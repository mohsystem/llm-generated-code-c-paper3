#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <base64.h>

void mainFunction() {
    char* testCases[] = {
        "Hello, World!",
        "This is a secret message",
        "Encryption is fun",
        "Cipher Block Chaining",
        "Secure your data"
    };
    char secretKey[] = "0123456789abcdef"; // 16 bytes for AES-128
    unsigned char iv[16] = {0}; // Initialization vector

    for (int i = 0; i < 5; ++i) {
        char* testCase = testCases[i];
        unsigned char* plaintextBytes = (unsigned char*)testCase;
        int plaintextSize = strlen(testCase);

        // Ensure plaintext is a multiple of block size (16 bytes for AES)
        int paddingSize = 16 - (plaintextSize % 16);
        unsigned char* paddedPlaintext = (unsigned char*)malloc(plaintextSize + paddingSize);
        memcpy(paddedPlaintext, plaintextBytes, plaintextSize);
        for (int j = 0; j < paddingSize; ++j) {
            paddedPlaintext[plaintextSize + j] = 0;
        }

        unsigned char* ciphertext = (unsigned char*)malloc(plaintextSize + paddingSize);
        AES_KEY aes_key;
        AES_set_encrypt_key((const unsigned char*)secretKey, 128, &aes_key);
        AES_cbc_encrypt(paddedPlaintext, ciphertext, plaintextSize + paddingSize, &aes_key, iv, AES_ENCRYPT);

        char* base64Encoded = base64_encode(ciphertext, plaintextSize + paddingSize);

        printf("Plaintext: %s\n", testCase);
        printf("Encrypted: %s\n", base64Encoded);

        free(paddedPlaintext);
        free(ciphertext);
        free(base64Encoded);
    }
}

int main() {
    mainFunction();
    return 0;
}