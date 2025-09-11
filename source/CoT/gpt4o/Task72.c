#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void encryptData(const unsigned char *inputData, int inputDataLen, unsigned char *outputData, int *outputDataLen) {
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH] = {0};

    RAND_bytes(key, 16); // Generate random AES key

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    int len;
    EVP_EncryptUpdate(ctx, outputData, &len, inputData, inputDataLen);
    *outputDataLen = len;

    EVP_EncryptFinal_ex(ctx, outputData + len, &len);
    *outputDataLen += len;

    EVP_CIPHER_CTX_free(ctx);
}

void printEncryptedData(const unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    const unsigned char testData1[] = "Test Data 1";
    const unsigned char testData2[] = "Test Data 2";
    const unsigned char testData3[] = "Test Data 3";
    const unsigned char testData4[] = "Test Data 4";
    const unsigned char testData5[] = "Test Data 5";

    unsigned char encryptedData[1024];
    int encryptedDataLen;

    encryptData(testData1, strlen((const char *)testData1), encryptedData, &encryptedDataLen);
    printEncryptedData(encryptedData, encryptedDataLen);

    encryptData(testData2, strlen((const char *)testData2), encryptedData, &encryptedDataLen);
    printEncryptedData(encryptedData, encryptedDataLen);

    encryptData(testData3, strlen((const char *)testData3), encryptedData, &encryptedDataLen);
    printEncryptedData(encryptedData, encryptedDataLen);

    encryptData(testData4, strlen((const char *)testData4), encryptedData, &encryptedDataLen);
    printEncryptedData(encryptedData, encryptedDataLen);

    encryptData(testData5, strlen((const char *)testData5), encryptedData, &encryptedDataLen);
    printEncryptedData(encryptedData, encryptedDataLen);

    return 0;
}