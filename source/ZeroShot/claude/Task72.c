
#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

#define MAX_INPUT_LENGTH 1024
#define AES_BLOCK_SIZE 16

static const unsigned char IV[16] = {0}; // Static IV filled with zeros

char* encrypt(const char* plaintext, const char* key) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        return NULL;
    }

    if(EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, 
                         (const unsigned char*)key, IV) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    int plaintext_len = strlen(plaintext);
    int len1, len2;
    unsigned char* ciphertext = malloc(plaintext_len + AES_BLOCK_SIZE);
    if(!ciphertext) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    if(EVP_EncryptUpdate(ctx, ciphertext, &len1,
                        (const unsigned char*)plaintext, plaintext_len) != 1) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    if(EVP_EncryptFinal_ex(ctx, ciphertext + len1, &len2) != 1) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    EVP_CIPHER_CTX_free(ctx);

    // Convert to hex string (simplified)
    char* result = malloc((len1 + len2) * 2 + 1);
    if(!result) {
        free(ciphertext);
        return NULL;
    }

    for(int i = 0; i < len1 + len2; i++) {
        sprintf(result + (i * 2), "%02x", ciphertext[i]);
    }
    
    free(ciphertext);
    return result;
}

int main() {
    const char* key = "1234567890123456"; // 16 byte key
    
    // Test cases
    const char* test_cases[] = {
        "Hello World!",
        "Secure Programming",
        "Test Case 3",
        "Encryption Test",
        "Final Test Case"
    };
    
    for(int i = 0; i < 5; i++) {
        char* encrypted = encrypt(test_cases[i], key);
        if(encrypted) {
            printf("Test case %d:\\n", i+1);
            printf("Original: %s\\n", test_cases[i]);
            printf("Encrypted: %s\\n\\n", encrypted);
            free(encrypted);
        } else {
            printf("Error encrypting test case %d\\n", i+1);
        }
    }
    
    return 0;
}
