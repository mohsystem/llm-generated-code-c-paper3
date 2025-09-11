
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define MAX_DATA_LEN 1024
#define KEY_LEN 32
#define IV_LEN 16

typedef struct {
    unsigned char key[KEY_LEN];
    unsigned char iv[IV_LEN];
    unsigned char* storage[5];  // Fixed size for simplicity
    size_t storage_len[5];
} Task124;

void init_encryption(Task124* handler) {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    
    // Generate random key and IV
    if(!RAND_bytes(handler->key, KEY_LEN) || 
       !RAND_bytes(handler->iv, IV_LEN)) {
        fprintf(stderr, "Failed to generate random key/IV\\n");
        exit(1);
    }
    
    // Initialize storage
    memset(handler->storage, 0, sizeof(handler->storage));
    memset(handler->storage_len, 0, sizeof(handler->storage_len));
}

void cleanup(Task124* handler) {
    // Free allocated memory
    for(int i = 0; i < 5; i++) {
        if(handler->storage[i]) {
            OPENSSL_cleanse(handler->storage[i], handler->storage_len[i]);
            free(handler->storage[i]);
        }
    }
    
    // Clean up OpenSSL
    EVP_cleanup();
}

int encrypt_data(Task124* handler, const unsigned char* plaintext, size_t plaintext_len,
                unsigned char** ciphertext, size_t* ciphertext_len) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        return 0;
    }

    if(!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, handler->key, handler->iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    *ciphertext = malloc(plaintext_len + EVP_MAX_BLOCK_LENGTH);
    if(!*ciphertext) {
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    int len1, len2;
    if(!EVP_EncryptUpdate(ctx, *ciphertext, &len1, plaintext, plaintext_len)) {
        free(*ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    if(!EVP_EncryptFinal_ex(ctx, *ciphertext + len1, &len2)) {
        free(*ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    *ciphertext_len = len1 + len2;
    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

int decrypt_data(Task124* handler, const unsigned char* ciphertext, size_t ciphertext_len,
                unsigned char** plaintext, size_t* plaintext_len) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        return 0;
    }

    if(!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, handler->key, handler->iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    *plaintext = malloc(ciphertext_len);
    if(!*plaintext) {
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    int len1, len2;
    if(!EVP_DecryptUpdate(ctx, *plaintext, &len1, ciphertext, ciphertext_len)) {
        free(*plaintext);
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    if(!EVP_DecryptFinal_ex(ctx, *plaintext + len1, &len2)) {
        free(*plaintext);
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    *plaintext_len = len1 + len2;
    EVP_', type='text')