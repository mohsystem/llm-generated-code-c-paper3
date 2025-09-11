#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void mainFunction() {
    char* testCases[] = {"Hello, World!", "This is a test string", "Cipher Block Chaining", "Encryption and Decryption", "Secure Communication"};
    for (int i = 0; i < 5; ++i) {
        unsigned char key[16] = "mysecretkey123";
        unsigned char iv[16] = "myiv123456";
        unsigned char* encrypted = encrypt(testCases[i], key, iv);
        unsigned char* decrypted = decrypt(encrypted, key, iv, strlen(testCases[i]));
        printf("Original: %s\n", testCases[i]);
        printf("Encrypted: ");
        for (int j = 0; j < strlen(testCases[i]) + (16 - (strlen(testCases[i]) % 16)); ++j) {
            printf("%02x", encrypted[j]);
        }
        printf("\n");
        printf("Decrypted: %s\n", decrypted);
        printf("\n");
        free(encrypted);
        free(decrypted);
    }
}

unsigned char* encrypt(const char* plaintext, unsigned char* key, unsigned char* iv) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    int blockSize = 16;
    int paddedLength = strlen(plaintext) + (blockSize - (strlen(plaintext) % blockSize));
    unsigned char* encrypted = malloc(paddedLength);
    unsigned char* plaintextPadded = malloc(paddedLength);

    // Pad the plaintext
    for (int i = 0; i < strlen(plaintext); ++i) {
        plaintextPadded[i] = plaintext[i];
    }
    for (int i = strlen(plaintext); i < paddedLength; ++i) {
        plaintextPadded[i] = ' ';
    }

    unsigned char* prevBlock = iv;
    for (int i = 0; i < paddedLength; i += blockSize) {
        for (int j = 0; j < blockSize; ++j) {
            plaintextPadded[i + j] ^= prevBlock[j];
        }
        AES_encrypt(plaintextPadded + i, encrypted + i, &aes_key);
        prevBlock = encrypted + i;
    }

    free(plaintextPadded);
    return encrypted;
}

unsigned char* decrypt(unsigned char* ciphertext, unsigned char* key, unsigned char* iv, int length) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    int blockSize = 16;
    int paddedLength = length + (blockSize - (length % blockSize));
    unsigned char* decrypted = malloc(paddedLength);
    unsigned char* prevBlock = iv;

    for (int i = 0; i < paddedLength; i += blockSize) {
        AES_decrypt(ciphertext + i, decrypted + i, &aes_key);
        for (int j = 0; j < blockSize; ++j) {
            decrypted[i + j] ^= prevBlock[j];
        }
        prevBlock = ciphertext + i;
    }

    return decrypted;
}

int main() {
    mainFunction();
    return 0;
}