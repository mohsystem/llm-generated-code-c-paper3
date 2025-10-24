#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define MAGIC "ENC1"
#define VERSION 1
#define SALT_LEN 16
#define IV_LEN 12
#define TAG_LEN 16
#define KEY_LEN 32
#define PBKDF2_ITERS 210000

static int is_symlink(const char* path) {
    struct stat st;
    if (lstat(path, &st) != 0) return 0;
    return S_ISLNK(st.st_mode);
}

static int starts_with(const char* str, const char* pre) {
    size_t lenpre = strlen(pre), lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

static int reject_symlinks_in_path(const char* base, const char* target) {
    char base_real[PATH_MAX];
    char tgt_real[PATH_MAX];
    if (!realpath(base, base_real)) return 0;
    if (!realpath(target, tgt_real)) {
        // If target doesn't exist (for write), check parent
        char copy[PATH_MAX];
        strncpy(copy, target, sizeof(copy)-1); copy[sizeof(copy)-1] = '\0';
        char* last = strrchr(copy, '/');
        if (last) {
            *last = '\0';
            if (!realpath(copy, tgt_real)) return 0;
        } else {
            strcpy(tgt_real, base_real);
        }
    }
    if (!starts_with(tgt_real, base_real)) return 0;

    // Walk components
    size_t blen = strlen(base_real);
    char path[PATH_MAX];
    strncpy(path, base_real, sizeof(path)-1); path[sizeof(path)-1] = '\0';
    size_t plen = strlen(path);
    if (plen + 1 < sizeof(path)) { path[plen] = '/'; path[plen+1] = '\0'; }

    const char* rel = tgt_real + blen;
    while (*rel == '/') rel++;
    char comp[PATH_MAX];
    while (*rel) {
        const char* slash = strchr(rel, '/');
        size_t clen = slash ? (size_t)(slash - rel) : strlen(rel);
        if (clen >= sizeof(comp)) return 0;
        memcpy(comp, rel, clen);
        comp[clen] = '\0';
        if (strlen(path) + clen + 1 >= sizeof(path)) return 0;
        strcat(path, comp);
        if (is_symlink(path)) return 0;
        if (slash) {
            strcat(path, "/");
            rel = slash + 1;
        } else break;
    }
    return 1;
}

static int resolve_safe_path(const char* base, const char* rel, int forWrite, char* out, size_t outsz) {
    if (!base || !rel || !out || outsz == 0) return 0;
    char base_real[PATH_MAX];
    if (!realpath(base, base_real)) return 0;
    struct stat st;
    if (stat(base_real, &st) != 0 || !S_ISDIR(st.st_mode)) return 0;
    if (rel[0] == '/') return 0;

    char candidate[PATH_MAX];
    snprintf(candidate, sizeof(candidate), "%s/%s", base_real, rel);

    char cand_real[PATH_MAX];
    if (!realpath(candidate, cand_real)) {
        // For write, target may not exist; resolve parent
        if (!forWrite) return 0;
        char parent[PATH_MAX];
        strncpy(parent, candidate, sizeof(parent)-1); parent[sizeof(parent)-1] = '\0';
        char* last = strrchr(parent, '/');
        if (!last) return 0;
        *last = '\0';
        char parent_real[PATH_MAX];
        if (!realpath(parent, parent_real)) return 0;
        if (!starts_with(parent_real, base_real)) return 0;
        snprintf(cand_real, sizeof(cand_real), "%s/%s", parent_real, last+1);
    }
    if (!starts_with(cand_real, base_real)) return 0;

    if (!forWrite) {
        if (stat(cand_real, &st) != 0 || !S_ISREG(st.st_mode)) return 0;
    } else {
        // Ensure parent dir exists
        char parent[PATH_MAX];
        strncpy(parent, cand_real, sizeof(parent)-1); parent[sizeof(parent)-1] = '\0';
        char* last = strrchr(parent, '/');
        if (!last) return 0;
        *last = '\0';
        if (stat(parent, &st) != 0 || !S_ISDIR(st.st_mode)) return 0;
        if (!reject_symlinks_in_path(base_real, parent)) return 0;
        if (lstat(cand_real, &st) == 0 && S_ISLNK(st.st_mode)) return 0;
    }
    if (!reject_symlinks_in_path(base_real, forWrite ? cand_real : cand_real)) return 0;
    strncpy(out, cand_real, outsz-1);
    out[outsz-1] = '\0';
    return 1;
}

static int read_file_all(const char* path, uint8_t** out, size_t* outlen) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long len = ftell(f);
    if (len < 0) { fclose(f); return 0; }
    rewind(f);
    uint8_t* buf = (uint8_t*)malloc((size_t)len);
    if (!buf && len != 0) { fclose(f); return 0; }
    if (len > 0 && fread(buf, 1, (size_t)len, f) != (size_t)len) { free(buf); fclose(f); return 0; }
    fclose(f);
    *out = buf;
    *outlen = (size_t)len;
    return 1;
}

static int atomic_write_chunks(const char* finalPath, const uint8_t** parts, const size_t* sizes, size_t count) {
    char dir[PATH_MAX];
    strncpy(dir, finalPath, sizeof(dir)-1); dir[sizeof(dir)-1] = '\0';
    char* last = strrchr(dir, '/');
    if (!last) return 0;
    *last = '\0';

    char tmpl[PATH_MAX];
    snprintf(tmpl, sizeof(tmpl), "%s/.tmpXXXXXX", dir);
    int fd = mkstemp(tmpl);
    if (fd < 0) return 0;
    fchmod(fd, 0600);

    for (size_t i = 0; i < count; i++) {
        const uint8_t* p = parts[i];
        size_t rem = sizes[i];
        while (rem > 0) {
            ssize_t w = write(fd, p, rem);
            if (w <= 0) { close(fd); unlink(tmpl); return 0; }
            p += w;
            rem -= (size_t)w;
        }
    }
    if (fsync(fd) != 0) { close(fd); unlink(tmpl); return 0; }
    if (close(fd) != 0) { unlink(tmpl); return 0; }
    if (rename(tmpl, finalPath) != 0) {
        unlink(tmpl);
        return 0;
    }
    chmod(finalPath, 0600);
    return 1;
}

static int derive_key(const char* passphrase, const uint8_t* salt, size_t saltlen, uint8_t* keyOut, size_t keylen) {
    if (PKCS5_PBKDF2_HMAC(passphrase, (int)strlen(passphrase), salt, (int)saltlen, PBKDF2_ITERS, EVP_sha256(), (int)keylen, keyOut) != 1) {
        return 0;
    }
    return 1;
}

int encrypt_file(const char* baseDir, const char* inputRel, const char* outputRel, const char* passphrase) {
    char inPath[PATH_MAX], outPath[PATH_MAX];
    if (!resolve_safe_path(baseDir, inputRel, 0, inPath, sizeof(inPath))) return 0;
    if (!resolve_safe_path(baseDir, outputRel, 1, outPath, sizeof(outPath))) return 0;

    uint8_t* plaintext = NULL;
    size_t pt_len = 0;
    if (!read_file_all(inPath, &plaintext, &pt_len)) return 0;

    uint8_t salt[SALT_LEN];
    uint8_t iv[IV_LEN];
    if (RAND_bytes(salt, SALT_LEN) != 1 || RAND_bytes(iv, IV_LEN) != 1) { free(plaintext); return 0; }

    uint8_t key[KEY_LEN];
    if (!derive_key(passphrase, salt, SALT_LEN, key, KEY_LEN)) { free(plaintext); return 0; }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) { free(plaintext); return 0; }
    uint8_t* ciphertext = (uint8_t*)malloc(pt_len > 0 ? pt_len : 1);
    if (!ciphertext && pt_len != 0) { EVP_CIPHER_CTX_free(ctx); free(plaintext); return 0; }
    int len = 0, outlen = 0;
    int ok = 1;

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) ok = 0;
    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, NULL) != 1) ok = 0;
    if (ok && EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv) != 1) ok = 0;
    if (ok && pt_len > 0) {
        if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)pt_len) != 1) ok = 0;
        outlen = len;
    } else outlen = 0;
    if (ok) {
        if (EVP_EncryptFinal_ex(ctx, ciphertext + outlen, &len) != 1) ok = 0;
        outlen += len;
    }
    uint8_t tag[TAG_LEN];
    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_LEN, tag) != 1) ok = 0;

    EVP_CIPHER_CTX_free(ctx);
    free(plaintext);
    if (!ok) { free(ciphertext); return 0; }

    uint8_t header[4 + 1 + SALT_LEN + IV_LEN];
    memcpy(header, MAGIC, 4);
    header[4] = VERSION;
    memcpy(header + 5, salt, SALT_LEN);
    memcpy(header + 5 + SALT_LEN, iv, IV_LEN);

    const uint8_t* parts[3];
    size_t sizes[3];
    parts[0] = header; sizes[0] = sizeof(header);
    parts[1] = ciphertext; sizes[1] = (size_t)outlen;
    parts[2] = tag; sizes[2] = TAG_LEN;

    int res = atomic_write_chunks(outPath, parts, sizes, 3);
    free(ciphertext);
    memset(key, 0, sizeof(key));
    return res;
}

int decrypt_file(const char* baseDir, const char* inputRel, const char* outputRel, const char* passphrase) {
    char inPath[PATH_MAX], outPath[PATH_MAX];
    if (!resolve_safe_path(baseDir, inputRel, 0, inPath, sizeof(inPath))) return 0;
    if (!resolve_safe_path(baseDir, outputRel, 1, outPath, sizeof(outPath))) return 0;

    uint8_t* data = NULL;
    size_t data_len = 0;
    if (!read_file_all(inPath, &data, &data_len)) return 0;
    size_t min_len = 4 + 1 + SALT_LEN + IV_LEN + TAG_LEN;
    if (data_len < min_len) { free(data); return 0; }
    if (memcmp(data, MAGIC, 4) != 0) { free(data); return 0; }
    if (data[4] != VERSION) { free(data); return 0; }

    size_t off = 5;
    uint8_t salt[SALT_LEN];
    memcpy(salt, data + off, SALT_LEN); off += SALT_LEN;
    uint8_t iv[IV_LEN];
    memcpy(iv, data + off, IV_LEN); off += IV_LEN;
    size_t ct_tag_len = data_len - off;
    if (ct_tag_len < TAG_LEN) { free(data); return 0; }
    size_t ct_len = ct_tag_len - TAG_LEN;

    uint8_t* ct = data + off;
    uint8_t* tag = data + off + ct_len;

    uint8_t key[KEY_LEN];
    if (!derive_key(passphrase, salt, SALT_LEN, key, KEY_LEN)) { free(data); return 0; }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) { free(data); return 0; }
    uint8_t* pt = (uint8_t*)malloc(ct_len > 0 ? ct_len : 1);
    if (!pt && ct_len != 0) { EVP_CIPHER_CTX_free(ctx); free(data); return 0; }
    int len = 0, outlen = 0;
    int ok = 1;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) ok = 0;
    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, NULL) != 1) ok = 0;
    if (ok && EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv) != 1) ok = 0;
    if (ok && ct_len > 0) {
        if (EVP_DecryptUpdate(ctx, pt, &len, ct, (int)ct_len) != 1) ok = 0;
        outlen = len;
    } else outlen = 0;

    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, TAG_LEN, tag) != 1) ok = 0;

    if (ok) {
        int ret = EVP_DecryptFinal_ex(ctx, pt + outlen, &len);
        if (ret != 1) ok = 0;
        else outlen += len;
    }

    EVP_CIPHER_CTX_free(ctx);
    free(data);
    memset(key, 0, sizeof(key));
    if (!ok) { free(pt); return 0; }

    const uint8_t* parts[1] = { pt };
    size_t sizes[1] = { (size_t)outlen };
    int res = atomic_write_chunks(outPath, parts, sizes, 1);
    free(pt);
    return res;
}

static int write_file_bytes(const char* path, const uint8_t* data, size_t len) {
    char dir[PATH_MAX];
    strncpy(dir, path, sizeof(dir)-1); dir[sizeof(dir)-1] = '\0';
    char* last = strrchr(dir, '/');
    if (last) { *last = '\0'; mkdir(dir, 0700); }
    FILE* f = fopen(path, "wb");
    if (!f) return 0;
    if (len > 0 && fwrite(data, 1, len, f) != len) { fclose(f); return 0; }
    fflush(f);
    int fd = fileno(f);
    fsync(fd);
    fclose(f);
    return 1;
}

int main(void) {
    char base[PATH_MAX];
    snprintf(base, sizeof(base), "%s/enc_base_c", P_tmpdir);
    mkdir(base, 0700);

    const char* pass = "StrongPassphrase!123";

    uint8_t empty[] = {0};
    uint8_t hello[] = "Hello, World!";
    const char* u8 = "\xE3\x81\x93\xE3\x82\x93\xE3\x81\xAB\xE3\x81\xA1\xE3\x81\xAF\xE4\xB8\x96\xE7\x95\x8C\xF0\x9F\x8C\x8F";

    uint8_t bin1[1024];
    RAND_bytes(bin1, sizeof bin1);
    uint8_t bin2[128 * 1024];
    RAND_bytes(bin2, sizeof bin2);

    struct {
        const uint8_t* data;
        size_t len;
    } tests[5] = {
        { empty, 0 },
        { hello, sizeof("Hello, World!") - 1 },
        { (const uint8_t*)u8, strlen(u8) },
        { bin1, sizeof(bin1) },
        { bin2, sizeof(bin2) }
    };

    int overall = 1;
    for (int i = 0; i < 5; i++) {
        char inRel[64], encRel[64], decRel[64];
        snprintf(inRel, sizeof(inRel), "input_%d.bin", i);
        snprintf(encRel, sizeof(encRel), "out_%d.enc", i);
        snprintf(decRel, sizeof(decRel), "dec_%d.bin", i);

        char inPath[PATH_MAX], encPath[PATH_MAX], decPath[PATH_MAX];
        snprintf(inPath, sizeof(inPath), "%s/%s", base, inRel);
        snprintf(encPath, sizeof(encPath), "%s/%s", base, encRel);
        snprintf(decPath, sizeof(decPath), "%s/%s", base, decRel);

        write_file_bytes(inPath, tests[i].data, tests[i].len);

        int ok1 = encrypt_file(base, inRel, encRel, pass);
        int ok2 = decrypt_file(base, encRel, decRel, pass);

        // Compare
        uint8_t* dec = NULL;
        size_t dec_len = 0;
        int match = 0;
        if (ok1 && ok2 && read_file_all(decPath, &dec, &dec_len)) {
            if (dec_len == tests[i].len && (tests[i].len == 0 || memcmp(dec, tests[i].data, tests[i].len) == 0)) {
                match = 1;
            }
            free(dec);
        }
        printf("Test %d => encrypt: %s, decrypt: %s, match: %s\n", i, ok1 ? "true" : "false", ok2 ? "true" : "false", match ? "true" : "false");
        if (!(ok1 && ok2 && match)) overall = 0;
    }
    printf("Overall: %s\n", overall ? "SUCCESS" : "FAIL");
    return overall ? 0 : 1;
}