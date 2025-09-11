#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>

void encrypt(const char *plaintext, unsigned char *ciphertext, int *ciphertext_len) {
    // Generate AES key
    unsigned char key[EVP_MAX_KEY_LENGTH];
    RAND_bytes(key, sizeof(key));

    // Static Initialization Vector
    unsigned char iv[AES_BLOCK_SIZE] = {0};  // AES block size is 16 bytes

    // Initialize Cipher
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    // Pad and Encrypt Data
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)plaintext, strlen(plaintext));
    *ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    *ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    unsigned char ciphertext[128];
    int ciphertext_len;

    encrypt("Test1", ciphertext, &ciphertext_len);
    fwrite(ciphertext, 1, ciphertext_len, stdout);
    printf("\n");

    encrypt("Test2", ciphertext, &ciphertext_len);
    fwrite(ciphertext, 1, ciphertext_len, stdout);
    printf("\n");

    encrypt("Test3", ciphertext, &ciphertext_len);
    fwrite(ciphertext, 1, ciphertext_len, stdout);
    printf("\n");

    encrypt("Test4", ciphertext, &ciphertext_len);
    fwrite(ciphertext, 1, ciphertext_len, stdout);
    printf("\n");

    encrypt("Test5", ciphertext, &ciphertext_len);
    fwrite(ciphertext, 1, ciphertext_len, stdout);
    printf("\n");

    return 0;
}