// Note: This example uses the tiny-AES-c library for simplicity.
// You need to include the tiny-AES-c library in your project.
#include "aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void aes_cbc_encrypt(uint8_t *key, uint8_t *iv, uint8_t *plaintext, uint8_t *ciphertext, size_t length) {
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, ciphertext, plaintext, length);
}

int main() {
    uint8_t key[32]; // 256 bits
    uint8_t iv[16]; // 128 bits
    // Generate random key and IV
    for (int i = 0; i < 32; i++) key[i] = rand() % 256;
    for (int i = 0; i < 16; i++) iv[i] = rand() % 256;

    const char *messages[] = {"This is a test message.", "Hello, AES!", "Encryption is secure.", "CBC mode is used.", "AES is widely adopted."};
    for (const char *message : messages) {
        size_t plaintext_len = strlen(message);
        size_t ciphertext_len = ((plaintext_len / AES_BLOCKLEN) + 1) * AES_BLOCKLEN; // Account for padding
        uint8_t ciphertext[ciphertext_len];
        aes_cbc_encrypt(key, iv, (uint8_t *)message, ciphertext, plaintext_len);
        printf("Encrypted Message: ");
        for (int i = 0; i < ciphertext_len; i++) {
            printf("%02x", ciphertext[i]);
        }
        printf("\n");
    }
    return 0;
}