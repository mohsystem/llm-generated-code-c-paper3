#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

#define MAGIC "ENC1"
#define VERSION 1
#define SALT_LEN 16
#define IV_LEN 12
#define TAG_LEN 16
#define KEY_LEN 32
#define ITERATIONS 210000

typedef struct {
    unsigned char* data;
    size_t len;
} Buffer;

static int rand_bytes(unsigned char* buf, int len) {
    return RAND_bytes(buf, len) == 1;
}

static int derive_key(const char* pass, const unsigned char* salt, unsigned char* outKey, int outLen) {
    return PKCS5_PBKDF2_HMAC(pass, (int)strlen(pass), salt, SALT_LEN, ITERATIONS, EVP_sha256(), outLen, outKey) == 1;
}

static int ct_equal(const unsigned char* a, const unsigned char* b, size_t len) {
    unsigned char r = 0;
    for (size_t i = 0; i < len; i++) r |= (unsigned char)(a[i] ^ b[i]);
    return r == 0;
}

static void free_buffer(Buffer b) {
    if (b.data) {
        OPENSSL_cleanse(b.data, b.len);
        free(b.data);
    }
}

Buffer encrypt_data(const char* passphrase, const unsigned char* plaintext, size_t pt_len) {
    Buffer out = {NULL, 0};
    if (!passphrase || (!plaintext && pt_len != 0)) return out;

    unsigned char salt[SALT_LEN];
    unsigned char iv[IV_LEN];
    unsigned char key[KEY_LEN];

    if (!rand_bytes(salt, SALT_LEN) || !rand_bytes(iv, IV_LEN)) return out;
    if (!derive_key(passphrase, salt, key, KEY_LEN)) return out;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return out;

    int ok = 1;
    int len1 = 0, len2 = 0;

    unsigned char* ciphertext = (unsigned char*)malloc(pt_len + TAG_LEN);
    if (!ciphertext) { EVP_CIPHER_CTX_free(ctx); return out; }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) ok = 0;
    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, NULL) != 1) ok = 0;
    if (ok && EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv) != 1) ok = 0;
    if (ok && EVP_EncryptUpdate(ctx, ciphertext, &len1, plaintext, (int)pt_len) != 1) ok = 0;
    if (ok && EVP_EncryptFinal_ex(ctx, ciphertext + len1, &len2) != 1) ok = 0;

    unsigned char tag[TAG_LEN];
    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_LEN, tag) != 1) ok = 0;

    if (!ok) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return out;
    }

    size_t ct_len = (size_t)(len1 + len2);
    size_t total = 4 + 1 + SALT_LEN + IV_LEN + ct_len + TAG_LEN;
    unsigned char* buf = (unsigned char*)malloc(total);
    if (!buf) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return out;
    }

    size_t pos = 0;
    memcpy(buf + pos, MAGIC, 4); pos += 4;
    buf[pos++] = VERSION;
    memcpy(buf + pos, salt, SALT_LEN); pos += SALT_LEN;
    memcpy(buf + pos, iv, IV_LEN); pos += IV_LEN;
    memcpy(buf + pos, ciphertext, ct_len); pos += ct_len;
    memcpy(buf + pos, tag, TAG_LEN); pos += TAG_LEN;

    out.data = buf;
    out.len = total;

    free(ciphertext);
    EVP_CIPHER_CTX_free(ctx);
    OPENSSL_cleanse(key, sizeof(key));
    return out;
}

Buffer decrypt_data(const char* passphrase, const unsigned char* blob, size_t blob_len) {
    Buffer out = {NULL, 0};
    if (!passphrase || !blob) return out;

    if (blob_len < 4 + 1 + SALT_LEN + IV_LEN + TAG_LEN) return out;
    if (memcmp(blob, MAGIC, 4) != 0) return out;
    if (blob[4] != VERSION) return out;

    size_t pos = 5;
    const unsigned char* salt = blob + pos; pos += SALT_LEN;
    const unsigned char* iv = blob + pos; pos += IV_LEN;

    size_t ct_and_tag_len = blob_len - pos;
    if (ct_and_tag_len < TAG_LEN) return out;

    size_t ct_len = ct_and_tag_len - TAG_LEN;
    const unsigned char* ct = blob + pos;
    const unsigned char* tag = blob + pos + ct_len;

    unsigned char key[KEY_LEN];
    if (!derive_key(passphrase, salt, key, KEY_LEN)) return out;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return out;

    unsigned char* plaintext = (unsigned char*)malloc(ct_len);
    if (!plaintext) { EVP_CIPHER_CTX_free(ctx); return out; }

    int ok = 1, len1 = 0, len2 = 0;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) ok = 0;
    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, NULL) != 1) ok = 0;
    if (ok && EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv) != 1) ok = 0;
    if (ok && EVP_DecryptUpdate(ctx, plaintext, &len1, ct, (int)ct_len) != 1) ok = 0;
    if (ok && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, TAG_LEN, (void*)tag) != 1) ok = 0;
    if (ok && EVP_DecryptFinal_ex(ctx, plaintext + len1, &len2) != 1) ok = 0;

    if (!ok) {
        free(plaintext);
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return out;
    }

    out.data = plaintext;
    out.len = (size_t)(len1 + len2);

    EVP_CIPHER_CTX_free(ctx);
    OPENSSL_cleanse(key, sizeof(key));
    return out;
}

int main(void) {
    const char* pass = "correct horse battery staple";
    const char* tests[5] = {
        "Hello, World!",
        "",
        "The quick brown fox jumps over the lazy dog",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "Unicode \xCF\x80 \xF0\x9F\x9A\x80"
    };

    for (int i = 0; i < 5; i++) {
        const unsigned char* pt = (const unsigned char*)tests[i];
        size_t pt_len = strlen(tests[i]);

        Buffer enc = encrypt_data(pass, pt, pt_len);
        Buffer dec = decrypt_data(pass, enc.data, enc.len);

        int ok = (dec.len == pt_len) && ct_equal(dec.data, pt, pt_len);
        printf("Test %d: %s encSize=%zu\n", i + 1, ok ? "OK" : "FAIL", enc.len);

        free_buffer(enc);
        free_buffer(dec);
    }
    return 0;
}