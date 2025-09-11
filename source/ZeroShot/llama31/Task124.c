#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

typedef struct {
    AES_KEY aes;
} Task124;

Task124* Task124_new() {
    Task124* task = malloc(sizeof(Task124));
    unsigned char key[32];
    RAND_bytes(key, 32);
    AES_key_init(key, 256, &task->aes);
    return task;
}

void Task124_encrypt(Task124* task, const char* data, char** encrypted, int* encryptedLen) {
    *encryptedLen = strlen(data);
    *encrypted = malloc(*encryptedLen);
    AES_encrypt((const unsigned char*)data, (unsigned char*)*encrypted, &task->aes);
}

void Task124_decrypt(Task124* task, const char* encryptedData, int encryptedLen, char** decrypted, int* decryptedLen) {
    *decryptedLen = encryptedLen;
    *decrypted = malloc(*decryptedLen);
    AES_decrypt((const unsigned char*)encryptedData, (unsigned char*)*decrypted, &task->aes);
}

int main() {
    Task124* task = Task124_new();
    const char* testCases[] = {
        "1234-5678-9012-3456", // Credit card number
        "John Doe", // Name
        "johndoe@example.com", // Email
        "123 Main St", // Address
        "12345" // ZIP code
    };

    for (int i = 0; i < 5; ++i) {
        const char* testCase = testCases[i];
        int encryptedLen;
        char* encrypted;
        Task124_encrypt(task, testCase, &encrypted, &encryptedLen);

        int decryptedLen;
        char* decrypted;
        Task124_decrypt(task, encrypted, encryptedLen, &decrypted, &decryptedLen);

        printf("Original: %s, Encrypted: %s, Decrypted: %s\n", testCase, encrypted, decrypted);

        free(encrypted);
        free(decrypted);
    }

    free(task);
    return 0;
}