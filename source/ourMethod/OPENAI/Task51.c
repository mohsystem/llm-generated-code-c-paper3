#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SALT_LEN 16
#define IV_LEN 12
#define TAG_LEN 16
#define ITERATIONS 210000
#define KEY_LEN 32

static const unsigned char MAGIC[4] = {'E','N','C','1'};
static const unsigned char VERSION = 0x01;

struct Buffer {
    unsigned char* data;
    size_t len;
};

static int get_random_bytes(unsigned char* buf, size_t len) {
    if (!buf || len == 0) return 0;
    return RAND_bytes(buf, (int)len) == 1;
}

static int derive_key(const char* passphrase, const unsigned char* salt, unsigned char* out_key, size_t out_key_len) {
    if (!passphrase || !salt || !out_key || out_key_len != KEY_LEN) return 0;
    int rc = PKCS5_PBKDF2_HMAC(passphrase, (int)strlen(passphrase), salt, SALT_LEN, ITERATIONS, EVP_sha256(), (int)out_key_len, out_key);
    return rc == 1;
}

static void free_buffer(struct Buffer* b) {
    if (b && b->data) {
        free(b->data);
        b->data = NULL;
        b->len = 0;
    }
}

static struct Buffer encrypt_string(const char* plaintext, const char* passphrase) {
    struct Buffer out = {NULL, 0};
    if (!plaintext || !passphrase) return out;

    unsigned char salt[SALT_LEN];
    unsigned char iv[IV_LEN];
    if (!get_random_bytes(salt, sizeof(salt)) || !get_random_bytes(iv, sizeof(iv))) {
        return out;
    }

    unsigned char key[KEY_LEN];
    if (!derive_key(passphrase, salt, key, sizeof(key))) {
        OPENSSL_cleanse(key, sizeof(key));
        return out;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        OPENSSL_cleanse(key, sizeof(key));
        return out;
    }

    int rc = 1;
    rc &= EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);
    rc &= EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, NULL);
    rc &= EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);
    if (rc != 1) {
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return out;
    }

    size_t pt_len = strlen(plaintext);
    unsigned char* ciphertext = NULL;
    int outlen = 0, tmplen = 0;
    if (pt_len > 0) {
        ciphertext = (unsigned char*)malloc(pt_len);
        if (!ciphertext) {
            EVP_CIPHER_CTX_free(ctx);
            OPENSSL_cleanse(key, sizeof(key));
            return out;
        }
        if (EVP_EncryptUpdate(ctx, ciphertext, &outlen, (const unsigned char*)plaintext, (int)pt_len) != 1) {
            free(ciphertext);
            EVP_CIPHER_CTX_free(ctx);
            OPENSSL_cleanse(key, sizeof(key));
            return out;
        }
    } else {
        ciphertext = (unsigned char*)malloc(1);
        if (!ciphertext) {
            EVP_CIPHER_CTX_free(ctx);
            OPENSSL_cleanse(key, sizeof(key));
            return out;
        }
        outlen = 0;
    }

    if (EVP_EncryptFinal_ex(ctx, ciphertext + outlen, &tmplen) != 1) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return out;
    }
    outlen += tmplen;

    unsigned char tag[TAG_LEN];
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_LEN, tag) != 1) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return out;
    }

    size_t total = sizeof(MAGIC) + 1 + SALT_LEN + IV_LEN + (size_t)outlen + TAG_LEN;
    unsigned char* blob = (unsigned char*)malloc(total);
    if (!blob) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return out;
    }
    size_t pos = 0;
    memcpy(blob + pos, MAGIC, sizeof(MAGIC)); pos += sizeof(MAGIC);
    blob[pos++] = VERSION;
    memcpy(blob + pos, salt, SALT_LEN); pos += SALT_LEN;
    memcpy(blob + pos, iv, IV_LEN); pos += IV_LEN;
    if (outlen > 0) memcpy(blob + pos, ciphertext, (size_t)outlen);
    pos += (size_t)outlen;
    memcpy(blob + pos, tag, TAG_LEN); pos += TAG_LEN;

    out.data = blob;
    out.len = total;

    free(ciphertext);
    EVP_CIPHER_CTX_free(ctx);
    OPENSSL_cleanse(key, sizeof(key));
    return out;
}

static int decrypt_string(const unsigned char* blob, size_t blob_len, const char* passphrase, char** out_plaintext, size_t* out_len) {
    if (!blob || !passphrase || !out_plaintext || !out_len) return 0;
    *out_plaintext = NULL;
    *out_len = 0;

    size_t min_len = sizeof(MAGIC) + 1 + SALT_LEN + IV_LEN + TAG_LEN;
    if (blob_len < min_len) return 0;
    if (CRYPTO_memcmp(blob, MAGIC, sizeof(MAGIC)) != 0) return 0;
    if (blob[sizeof(MAGIC)] != VERSION) return 0;

    size_t pos = sizeof(MAGIC) + 1;
    const unsigned char* salt = blob + pos; pos += SALT_LEN;
    const unsigned char* iv = blob + pos; pos += IV_LEN;
    if (blob_len < pos + TAG_LEN) return 0;
    size_t ct_len = blob_len - pos - TAG_LEN;
    const unsigned char* ct = blob + pos;
    const unsigned char* tag = blob + pos + ct_len;

    unsigned char key[KEY_LEN];
    if (!derive_key(passphrase, salt, key, sizeof(key))) {
        OPENSSL_cleanse(key, sizeof(key));
        return 0;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        OPENSSL_cleanse(key, sizeof(key));
        return 0;
    }

    int rc = 1;
    rc &= EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);
    rc &= EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, NULL);
    rc &= EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);
    if (rc != 1) {
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return 0;
    }

    unsigned char* pt = NULL;
    int outl = 0, fin = 0;
    if (ct_len > 0) {
        pt = (unsigned char*)malloc(ct_len);
        if (!pt) {
            EVP_CIPHER_CTX_free(ctx);
            OPENSSL_cleanse(key, sizeof(key));
            return 0;
        }
        if (EVP_DecryptUpdate(ctx, pt, &outl, ct, (int)ct_len) != 1) {
            free(pt);
            EVP_CIPHER_CTX_free(ctx);
            OPENSSL_cleanse(key, sizeof(key));
            return 0;
        }
    } else {
        pt = (unsigned char*)malloc(1);
        if (!pt) {
            EVP_CIPHER_CTX_free(ctx);
            OPENSSL_cleanse(key, sizeof(key));
            return 0;
        }
        outl = 0;
    }

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, TAG_LEN, (void*)tag) != 1) {
        free(pt);
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return 0;
    }

    if (EVP_DecryptFinal_ex(ctx, pt + outl, &fin) != 1) {
        free(pt);
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return 0;
    }
    outl += fin;

    char* result = (char*)malloc((size_t)outl + 1);
    if (!result) {
        free(pt);
        EVP_CIPHER_CTX_free(ctx);
        OPENSSL_cleanse(key, sizeof(key));
        return 0;
    }
    if (outl > 0) memcpy(result, pt, (size_t)outl);
    result[outl] = '\0';

    *out_plaintext = result;
    *out_len = (size_t)outl;

    free(pt);
    EVP_CIPHER_CTX_free(ctx);
    OPENSSL_cleanse(key, sizeof(key));
    return 1;
}

int main(void) {
    const char* tests[5] = {
        "",
        "hello",
        "The quick brown fox jumps over the lazy dog.",
        "Numbers 1234567890!@#",
        "Repeat message repeat message repeat message."
    };
    const char* passphrase = "Strong Passphrase 2025!";
    int ok = 0;

    for (int i = 0; i < 5; i++) {
        struct Buffer blob = encrypt_string(tests[i], passphrase);
        if (blob.data == NULL || blob.len == 0) {
            printf("Test %d FAIL\n", i + 1);
            continue;
        }
        char* dec = NULL;
        size_t dec_len = 0;
        int success = decrypt_string(blob.data, blob.len, passphrase, &dec, &dec_len);
        if (success && dec != NULL) {
            int equal = (strlen(tests[i]) == dec_len) &&
                        (CRYPTO_memcmp(tests[i], dec, dec_len) == 0);
            if (equal) {
                printf("Test %d OK\n", i + 1);
                ok++;
            } else {
                printf("Test %d FAIL\n", i + 1);
            }
        } else {
            printf("Test %d FAIL\n", i + 1);
        }
        if (dec) {
            free(dec);
        }
        free_buffer(&blob);
    }
    if (ok != 5) {
        return 1;
    }
    return 0;
}