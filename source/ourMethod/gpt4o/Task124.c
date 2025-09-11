#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void handleErrors() {
    fprintf(stderr, "Error occurred\n");
    exit(1);
}

void encrypt(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

void decrypt(const unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    int plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    unsigned char key[16];
    unsigned char iv[16];

    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    const char* sensitiveData[5] = {
        "4111111111111111",
        "John Doe",
        "123456789",
        "01/23",
        "987"
    };

    unsigned char encrypted[128];
    unsigned char decrypted[128];

    for (int i = 0; i < 5; i++) {
        encrypt((unsigned char*)sensitiveData[i], strlen(sensitiveData[i]), key, iv, encrypted);
        decrypt(encrypted, strlen((char*)encrypted), key, iv, decrypted);
        decrypted[strlen((char*)sensitiveData[i])] = '\0';
        printf("Decrypted: %s\n", decrypted);
    }

    return 0;
}