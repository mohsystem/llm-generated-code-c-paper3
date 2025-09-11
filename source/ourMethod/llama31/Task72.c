#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/err.h>

void encrypt(const unsigned char* data, size_t dataLen, unsigned char* encrypted) {
    const unsigned char iv[] = "0123456789abcdef"; // Static IV
    const unsigned char key[] = "0123456789abcdef0123456789abcdef"; // 256-bit key

    AES_KEY aesKey;
    AES_set_encrypt_key(key, 256, &aesKey);

    int blockSize = AES_BLOCK_SIZE;
    int paddingSize = blockSize - (dataLen % blockSize);
    unsigned char* paddedData = malloc(dataLen + paddingSize);
    memcpy(paddedData, data, dataLen);
    for (int i = dataLen; i < dataLen + paddingSize; i++) {
        paddedData[i] = paddingSize;
    }

    AES_cbc_encrypt(paddedData, encrypted, dataLen + paddingSize, &aesKey, iv, AES_ENCRYPT);

    free(paddedData);
}

int main() {
    const char* data[] = {"Hello, World!", "This is a test.", "Encryption example."};
    for (const char* datum : data) {
        size_t dataLen = strlen(datum);
        unsigned char* encrypted = malloc(dataLen + 16); // Allow for padding
        encrypt((const unsigned char*)datum, dataLen, encrypted);

        for (size_t i = 0; i < dataLen + 16; i++) {
            printf("%02x", encrypted[i]);
        }
        printf("\n");

        free(encrypted);
    }
    return 0;
}