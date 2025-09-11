#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt(const unsigned char* plaintext, int plaintext_len, unsigned char* key, unsigned char* iv, unsigned char* ciphertext) {
    EVP_CIPHER_CTX* ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int main() {
    unsigned char key[] = "0123456789abcdef0123456789abcdef";
    unsigned char iv[] = "0123456789abcdef";
    const char* testCases[] = {"Hello", "World", "This is a test", "Encryption in C", "AES CBC Mode"};
    int testCaseCount = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < testCaseCount; ++i) {
        const char* data = testCases[i];
        int dataLen = strlen(data);
        int blockSize = 16; // AES block size in bytes
        int paddingSize = blockSize - (dataLen % blockSize);
        unsigned char paddedData[dataLen + paddingSize];
        memcpy(paddedData, data, dataLen);
        for (int j = dataLen; j < dataLen + paddingSize; ++j) {
            paddedData[j] = paddingSize;
        }

        unsigned char ciphertext[dataLen + paddingSize];
        int ciphertextLen = encrypt(paddedData, dataLen + paddingSize, key, iv, ciphertext);

        for (int j = 0; j < ciphertextLen; ++j) {
            printf("%02x", ciphertext[j]);
        }
        printf("\n");
    }

    return 0;
}