#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>

void encrypt(const char *data, const unsigned char *key, unsigned char *encrypted) {
    unsigned char static_iv[16];
    RAND_bytes(static_iv, sizeof(static_iv)); // static IV for demonstration purposes

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, static_iv);

    int len;
    EVP_EncryptUpdate(ctx, encrypted, &len, (const unsigned char *)data, strlen(data));
    int ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, encrypted + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

void print_encrypted(const unsigned char *encrypted, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", encrypted[i]);
    }
    printf("\n");
}

void run_tests() {
    unsigned char key[16];
    RAND_bytes(key, sizeof(key));

    unsigned char encrypted[128];
    int len = sizeof(encrypted);

    encrypt("Test1", key, encrypted);
    print_encrypted(encrypted, len);

    encrypt("Test2", key, encrypted);
    print_encrypted(encrypted, len);

    encrypt("Test3", key, encrypted);
    print_encrypted(encrypted, len);

    encrypt("Test4", key, encrypted);
    print_encrypted(encrypted, len);

    encrypt("Test5", key, encrypted);
    print_encrypted(encrypted, len);
}

int main() {
    run_tests();
    return 0;
}