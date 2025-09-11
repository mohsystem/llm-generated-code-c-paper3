#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <base64.h>

char *encrypt_aes(const char *key, const char *input) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char *ciphertext;

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key, iv);

    ciphertext = malloc(strlen(input) + AES_BLOCK_SIZE);
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)input, strlen(input));
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    char *encoded = malloc(ciphertext_len * 2);
    base64_encode(ciphertext, ciphertext_len, encoded);

    free(ciphertext);

    return encoded;
}

int main() {
    const char *key = "1234567890123456";
    const char *test_cases[5] = {"Test1", "Test2", "Test3", "Test4", "Test5"};
    for (int i = 0; i < 5; i++) {
        char *encrypted = encrypt_aes(key, test_cases[i]);
        printf("Encrypted: %s\n", encrypted);
        free(encrypted);
    }
    return 0;
}