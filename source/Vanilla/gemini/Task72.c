#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>


static const unsigned char iv[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

char *encrypt(const char *data, const char *key) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;
    char *ciphertext = (char *)malloc(128); // Allocate sufficient memory

    if(!(ctx = EVP_CIPHER_CTX_new())) {
        fprintf(stderr, "Error creating cipher context\n");
        exit(1);
    }

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (const unsigned char *)key, iv)) {
        fprintf(stderr, "Error initializing encryption\n");
        exit(1);
    }

    // Pad the input data
    int data_len = strlen(data);
    int padding = 16 - (data_len % 16);
    if(padding == 16) padding = 0;


    char padded_data[data_len + padding];
    strcpy(padded_data, data);
    for (int i = 0; i < padding; i++) {
        padded_data[data_len + i] = '\0';
    }

    if(1 != EVP_EncryptUpdate(ctx, (unsigned char *)ciphertext, &len, (const unsigned char *)padded_data, data_len+padding)) {
         fprintf(stderr, "Error encrypting data\n");
         exit(1);
    }
    ciphertext_len = len;


    if(1 != EVP_EncryptFinal_ex(ctx, (unsigned char *)ciphertext + len, &len)) {
         fprintf(stderr, "Error finalizing encryption\n");
         exit(1);
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    ciphertext[ciphertext_len] = '\0'; // Null-terminate the ciphertext

    return ciphertext;
}

int main() {
    char *key = "MySuperSecretKey1";
    char *testCases[] = {"Hello", "World", "This is a test", "Another test case", "A longer string to test padding"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char *encrypted = encrypt(testCases[i], key);
        printf("Original: %s\n", testCases[i]);
        printf("Encrypted: ");
        for(int j = 0; j < strlen(encrypted); j++) {
             printf("%02x", (unsigned char)encrypted[j]);
        }
        printf("\n");

        free(encrypted); // Free the allocated memory
    }
    return 0;
}