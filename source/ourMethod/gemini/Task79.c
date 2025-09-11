#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>


// Helper function to handle OpenSSL errors
void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}


char* encryptMessage(const char* message, const char* secretKey) {

    // ... (Implementation for AES encryption using OpenSSL) ...
 // Decode the base64 encoded key
    size_t keyLen = 0;
    unsigned char* decodedKey = EVP_DecodeBlock(NULL, (const unsigned char*)secretKey, strlen(secretKey), &keyLen);
    if (!decodedKey || keyLen != AES_BLOCK_SIZE) {
        // Handle key decoding error
        char* error_message = (char*)malloc(100 * sizeof(char)); 
        strcpy(error_message, "Error: Invalid key length or format.");
        return error_message;
    }

     // ... rest of your encryption logic using decodedKey ...



}

int main() {
    // Test cases
    const char* testCases[][2] = {
        {"Hello", "InvalidKey"},
        {"Hello", "c2VjcmV0IGtleQ=="}, //valid key
        {"World", "c2VjcmV0IGtleQ=="},
        {"This is a test", "c2VjcmV0IGtleQ=="},
        {"", "c2VjcmV0IGtleQ=="}
    };

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {

        char *encryptedMessage = encryptMessage(testCases[i][0], testCases[i][1]);
        printf("Original Message: %s\n", testCases[i][0]);
        printf("Encrypted Message: %s\n", encryptedMessage);
        free(encryptedMessage); // Free the allocated memory

        printf("--------------------\n");
    }



    unsigned char key[AES_BLOCK_SIZE];
    RAND_bytes(key, AES_BLOCK_SIZE);

    // Encode the key to base64
    size_t encodedKeyLen = 0;
    unsigned char* encodedKey = EVP_EncodeBlock(NULL, key, AES_BLOCK_SIZE, &encodedKeyLen);
    if (!encodedKey) {
        handleErrors();
    }
    char* base64Key = (char*)malloc((encodedKeyLen + 1) * sizeof(char));
    memcpy(base64Key, encodedKey, encodedKeyLen);
    base64Key[encodedKeyLen] = '\0';

    printf("Generated Key (Base64): %s\n", base64Key);

    OPENSSL_free(encodedKey);
    free(base64Key); // Free the allocated memory



    return 0;
}