#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <base64.h> // Include a suitable base64 library

static unsigned char iv[16];

static const unsigned char key[] = "ThisIsASecretKey"; // Replace with stronger key generation


char* encrypt(const char* data) {
    RAND_bytes(iv, 16); // Generate random IV for each encryption

    int data_len = strlen(data);
    int padded_len = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE * AES_BLOCK_SIZE;
    unsigned char *padded_data = (unsigned char *)malloc(padded_len);
    memcpy(padded_data, data, data_len);

    for (int i = data_len; i < padded_len; ++i) {
        padded_data[i] = padded_len - data_len;  // PKCS#7 padding
    }


     EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    
    unsigned char *encrypted_data = (unsigned char*)malloc(padded_len + AES_BLOCK_SIZE);
    int encrypted_len;
    EVP_EncryptUpdate(ctx, encrypted_data, &encrypted_len, padded_data, padded_len);

    int final_len;
    EVP_EncryptFinal_ex(ctx, encrypted_data + encrypted_len, &final_len);
    encrypted_len += final_len;

    EVP_CIPHER_CTX_free(ctx);
    free(padded_data);



    char *base64_encrypted = base64_encode(encrypted_data, encrypted_len);
    free(encrypted_data);
    return base64_encrypted;
}

int main() {
    char *testCases[] = {"Hello", "World", "This is a test", "Another test case", "Short"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char *encrypted = encrypt(testCases[i]);
        printf("Encrypted: %s\n", encrypted);
         free(encrypted); // Free the allocated memory
    }

    return 0;
}