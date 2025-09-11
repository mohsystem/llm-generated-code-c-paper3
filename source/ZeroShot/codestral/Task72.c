// C does not have built-in support for AES encryption, so we use OpenSSL library.
// Install OpenSSL library before running the code.
// gcc -o encrypt encrypt.c -lcrypto

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned char IV[AES_BLOCK_SIZE] = {0};

void encrypt(const char* input, const char* key, char** encrypted) {
    AES_KEY aesKey;
    AES_set_encrypt_key((const unsigned char*)key, 128, &aesKey);

    int inputLength = strlen(input);
    int paddingLength = AES_BLOCK_SIZE - inputLength % AES_BLOCK_SIZE;
    int paddedLength = inputLength + paddingLength;

    unsigned char* paddedInput = malloc(paddedLength);
    memcpy(paddedInput, input, inputLength);
    memset(paddedInput + inputLength, paddingLength, paddingLength);

    *encrypted = malloc(paddedLength);
    for (int i = 0; i < paddedLength; i += AES_BLOCK_SIZE) {
        AES_encrypt(paddedInput + i, (unsigned char*)(*encrypted) + i, &aesKey);
    }

    free(paddedInput);
}

int main() {
    char* key = "1234567890123456";
    char* encrypted;

    encrypt("Hello, World!", key, &encrypted);
    printf("%s\n", encrypted);
    free(encrypted);

    encrypt("Secure data encryption", key, &encrypted);
    printf("%s\n", encrypted);
    free(encrypted);

    encrypt("AES CBC Mode", key, &encrypted);
    printf("%s\n", encrypted);
    free(encrypted);

    encrypt("Padding is important", key, &encrypted);
    printf("%s\n", encrypted);
    free(encrypted);

    encrypt("Test case number five", key, &encrypted);
    printf("%s\n", encrypted);
    free(encrypted);

    return 0;
}