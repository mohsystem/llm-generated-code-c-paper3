#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>

void encrypt_message(const char *message, unsigned char *key, char *output) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    int len;
    unsigned char ciphertext[strlen(message) + AES_BLOCK_SIZE];
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)message, strlen(message));

    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    for(int i = 0; i < ciphertext_len; ++i) {
        sprintf(output + i * 2, "%02x", ciphertext[i]);
    }
}

int main() {
    unsigned char key[16];
    RAND_bytes(key, sizeof(key));

    char encrypted[128];
    encrypt_message("Hello", key, encrypted);
    printf("%s\n", encrypted);

    encrypt_message("World", key, encrypted);
    printf("%s\n", encrypted);

    encrypt_message("C", key, encrypted);
    printf("%s\n", encrypted);

    encrypt_message("Encryption", key, encrypted);
    printf("%s\n", encrypted);

    encrypt_message("Test", key, encrypted);
    printf("%s\n", encrypted);

    return 0;
}