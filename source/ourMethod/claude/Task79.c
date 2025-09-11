
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define KEY_SIZE 16
#define IV_SIZE 16
#define MAX_ENCRYPTED_SIZE 1024

static const char base64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char* base64_encode(const unsigned char* data, int length) {
    char* result = (char*)malloc(((length + 2) / 3) * 4 + 1);
    if(!result) return NULL;
    
    int i = 0;
    int j = 0;
    unsigned char array3[3];
    unsigned char array4[4];
    int result_index = 0;
    
    while(length--) {
        array3[i++] = *(data++);
        if(i == 3) {
            array4[0] = (array3[0] & 0xfc) >> 2;
            array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
            array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
            array4[3] = array3[2] & 0x3f;
            
            for(i = 0; i < 4; i++)
                result[result_index++] = base64_chars[array4[i]];
            i = 0;
        }
    }
    
    if(i) {
        int j;
        for(j = i; j < 3; j++)
            array3[j] = '\\0';
            
        array4[0] = (array3[0] & 0xfc) >> 2;
        array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
        array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
        
        for(j = 0; j < i + 1; j++)
            result[result_index++] = base64_chars[array4[j]];
            
        while(i++ < 3)
            result[result_index++] = '=';
    }
    
    result[result_index] = '\\0';
    return result;
}

char* encrypt_message(const char* message, const char* key) {
    if(!message || !key || !strlen(message) || !strlen(key)) {
        return NULL;
    }
    
    // Initialize OpenSSL
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        return NULL;
    }
    
    // Prepare key
    unsigned char key_data[KEY_SIZE];
    memset(key_data, 0, KEY_SIZE);
    memcpy(key_data, key, strlen(key) < KEY_SIZE ? strlen(key) : KEY_SIZE);
    
    // Generate IV
    unsigned char iv[IV_SIZE];
    if(RAND_bytes(iv, IV_SIZE) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }
    
    // Initialize encryption
    if(EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key_data, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }
    
    // Prepare output buffer
    unsigned char* encrypted = (unsigned char*)malloc(MAX_ENCRYPTED_SIZE);
    if(!encrypted) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }
    memcpy(encrypted, iv, IV_SIZE);
    
    int len;
    int ciphertext_len;
    
    // Encrypt
    if(EVP_EncryptUpdate(ctx, encrypted + IV_SIZE, &len, 
                        (const unsigned char*)message, strlen(message)) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(encrypted);
        return NULL;
    }
    ciphertext_len = len;
    
    // Finalize encryption
    if(EVP_EncryptFinal_ex(ctx, encrypted + IV_SIZE + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(encrypted);
        return NULL;
    }
    ciphertext_len += len;
    
    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    
    // Base64 encode the result
    char* result = base64_encode(encrypted, IV_SIZE + ciphertext_', type='text')