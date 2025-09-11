// Note: This implementation is simplified and uses the tiny-AES-c library.
// For a full and secure implementation, consider using a more robust library like OpenSSL.

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "aes.h"

void encrypt_aes(const uint8_t* data, size_t dataSize, const uint8_t* key, uint8_t* output) {
    // Create a static IV
    uint8_t iv[16];
    memset(iv, 0, 16);

    // Initialize the cipher context
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    // Pad the data to match the block size
    size_t blockSize = 16;
    size_t paddingSize = blockSize - (dataSize % blockSize);
    uint8_t paddedData[dataSize + paddingSize];
    memcpy(paddedData, data, dataSize);
    for (size_t i = dataSize; i < dataSize + paddingSize; i++) {
        paddedData[i] = (uint8_t)paddingSize;
    }

    // Encrypt the padded data
    AES_CBC_encrypt_buffer(&ctx, paddedData, dataSize + paddingSize);

    // Copy the IV and the encrypted data to the output
    memcpy(output, iv, 16);
    memcpy(output + 16, paddedData, dataSize + paddingSize);
}

int main() {
    uint8_t key[] = "0123456789abcdef"; // 16 bytes for AES-128
    const char* testCases[] = {
        "Hello, AES!",
        "This is a test string.",
        "Short string.",
        "Very long string to test padding.",
        "Another test string with different length."
    };

    for (size_t i = 0; i < 5; i++) {
        size_t dataSize = strlen(testCases[i]);
        uint8_t output[dataSize + 16 + (16 - (dataSize % 16))];
        encrypt_aes((const uint8_t*)testCases[i], dataSize, key, output);

        for (size_t j = 0; j < sizeof(output); j++) {
            printf("%02x", output[j]);
        }
        printf("\n");
    }

    return 0;
}