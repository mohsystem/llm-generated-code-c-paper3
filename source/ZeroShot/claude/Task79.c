
#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define MAX_MESSAGE_LENGTH 1024
#define KEY_LENGTH 16

char* encrypt(const char* message, const char* secret_key) {
    static char encrypted[MAX_MESSAGE_LENGTH * 2];  // Extra space for base64 encoding
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        return "Error creating cipher context";
    }
    
    if(!EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, 
                          (const unsigned char*)secret_key, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return "Error initializing encryption";
    }
    
    unsigned char ciphertext[MAX_MESSAGE_LENGTH];
    int len1, len2;
    
    if(!EVP_EncryptUpdate(ctx, ciphertext, &len1,
                         (const unsigned char*)message, strlen(message))) {
        EVP_CIPHER_CTX_free(ctx);
        return "Error in encryption update";
    }
    
    if(!EVP_EncryptFinal_ex(ctx, ciphertext + len1, &len2)) {
        EVP_CIPHER_CTX_free(ctx);
        return "Error in encryption final";
    }
    
    // Base64 encode the result
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    
    BIO_write(bio, ciphertext, len1 + len2);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    
    memcpy(encrypted, bufferPtr->data, bufferPtr->length);
    encrypted[bufferPtr->length] = '\\0';
    
    BIO_free_all(bio);
    EVP_CIPHER_CTX_free(ctx);
    
    return encrypted;
}

int main() {
    const char* key = "1234567890123456"; // 16 byte key for AES-128
    
    // Test cases
    const char* messages[] = {
        "Hello World",
        "Secret Message 123",
        "Confidential Data",
        "Test Message",
        "Encryption Test"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Test case %d:\\n", i+1);
        printf("Original: %s\\n", messages[i]);
        printf("Encrypted: %s\\n\\n", encrypt(messages[i], key));
    }
    
    return 0;
}
