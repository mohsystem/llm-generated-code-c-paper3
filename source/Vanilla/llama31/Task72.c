#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "aes.h" // From kokke/tiny-AES-c

void aes_cbc_encrypt(uint8_t *key, uint8_t *iv, uint8_t *plaintext, uint8_t *ciphertext, size_t plaintext_len) {
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    size_t blockSize = AES_BLOCKLEN;
    size_t paddingSize = blockSize - (plaintext_len % blockSize);
    size_t paddedLen = plaintext_len + paddingSize;

    uint8_t *paddedPlaintext = malloc(paddedLen);
    memcpy(paddedPlaintext, plaintext, plaintext_len);
    for (size_t i = plaintext_len; i < paddedLen; i++) {
        paddedPlaintext[i] = (uint8_t) paddingSize;
    }

    AES_CBC_encrypt_buffer(&ctx, paddedPlaintext, paddedLen);
    memcpy(ciphertext, paddedPlaintext, paddedLen);

    free(paddedPlaintext);
}

int main() {
    uint8_t key[32]; // 256-bit key
    uint8_t iv[16]; // 128-bit IV
    // Initialize key and IV (for example, with zeros)
    memset(key, 0, 32);
    memset(iv, 0, 16);

    const char *testCases[] = {
        "This is a test message.",
        "Another test message.",
        "Short message.",
        "Very long message that needs padding.",
        "Single block message."
    };

    for (const char *testCase : testCases) {
        size_t plaintextLen = strlen(testCase);
        uint8_t *ciphertext = malloc(plaintextLen + AES_BLOCKLEN);
        aes_cbc_encrypt(key, iv, (uint8_t*)testCase, ciphertext, plaintextLen);

        printf("Encrypted: ");
        for (size_t i = 0; i < plaintextLen + AES_BLOCKLEN; i++) {
            printf("%02x", ciphertext[i]);
        }
        printf("\n");

        free(ciphertext);
    }

    return 0;
}