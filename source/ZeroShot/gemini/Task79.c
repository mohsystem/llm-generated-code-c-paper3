#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>


//  Similar to C++ implementation, uses OpenSSL.  Error handling and IV generation 
//  should be improved for production code.

char* encryptMessage(const char* message, const char* secretKey) {
    unsigned char key[16];
    strncpy((char*)key, secretKey, sizeof(key));
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE); 

    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    int ciphertextLen = strlen(message) + AES_BLOCK_SIZE;
    unsigned char ciphertext[ciphertextLen];

    AES_cbc_encrypt((unsigned char*)message, ciphertext, strlen(message), &aesKey, iv, AES_ENCRYPT);

    char* encryptedHex = (char*)malloc(ciphertextLen * 2 + 1);  // Allocate memory
    if (!encryptedHex) {
        perror("Memory allocation failed");
        return NULL;
    }

    for (int i = 0; i < ciphertextLen; ++i) {
        sprintf(encryptedHex + i * 2, "%02x", ciphertext[i]);
    }

    return encryptedHex;
}

int main() {
    char* messages[] = {"Hello", "World", "Test1", "Test2", "Test3"};
    char* secretKey = "MySecretKey123";

    for (int i = 0; i < 5; i++) {
        char* encryptedMessage = encryptMessage(messages[i], secretKey);
        if (encryptedMessage) {
            printf("Encrypted: %s\n", encryptedMessage);
            free(encryptedMessage); // Free allocated memory
        }

    }
    return 0;
}