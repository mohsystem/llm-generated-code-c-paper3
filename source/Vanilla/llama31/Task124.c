#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/rand.h>

void encrypt(const char* data, char* encrypted) {
    unsigned char key[32];
    RAND_bytes(key, 32);

    AES_KEY aes_key;
    AES_set_encrypt_key(key, 256, &aes_key);

    unsigned char* encryptedBytes = (unsigned char*)malloc(strlen(data));
    AES_encrypt((const unsigned char*)data, encryptedBytes, &aes_key);

    sprintf(encrypted, "%s:%s", (char*)encryptedBytes, (char*)key);
    free(encryptedBytes);
}

void decrypt(const char* encrypted, char* decrypted) {
    size_t colonPos = strchr(encrypted, ':') - encrypted;
    char encryptedStr[colonPos + 1];
    strncpy(encryptedStr, encrypted, colonPos);
    encryptedStr[colonPos] = '\0';

    char key[33];
    strncpy(key, encrypted + colonPos + 1, 32);
    key[32] = '\0';

    unsigned char keyBytes[32];
    memcpy(keyBytes, key, 32);

    AES_KEY aes_key;
    AES_set_decrypt_key(keyBytes, 256, &aes_key);

    unsigned char* decryptedBytes = (unsigned char*)malloc(strlen(encryptedStr));
    AES_decrypt((const unsigned char*)encryptedStr, decryptedBytes, &aes_key);

    sprintf(decrypted, "%s", (char*)decryptedBytes);
    free(decryptedBytes);
}

int main() {
    char testCases[][20] = {
        "1234-5678-9012-3456",
        "John Doe",
        "123 Main St",
        "123-456-7890",
        "johndoe@example.com"
    };

    for (int i = 0; i < 5; ++i) {
        char encrypted[100];
        encrypt(testCases[i], encrypted);

        char decrypted[100];
        decrypt(encrypted, decrypted);

        printf("Original: %s\n", testCases[i]);
        printf("Encrypted: %s\n", encrypted);
        printf("Decrypted: %s\n\n", decrypted);
    }

    return 0;
}