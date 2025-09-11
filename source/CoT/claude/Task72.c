
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define KEY_SIZE 16
#define BLOCK_SIZE 16

static unsigned char iv[KEY_SIZE];

// Initialize IV
void initialize() {
    RAND_bytes(iv, KEY_SIZE);
}

// Encrypt function
char* encrypt(const char* data, const char* key) {
    if(!data || !key) {
        fprintf(stderr, "Input data and key cannot be null\\n");
        return NULL;
    }

    // Create and initialize context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        fprintf(stderr, "Failed to create cipher context\\n");
        return NULL;
    }

    // Create padded key
    unsigned char padded_key[KEY_SIZE];
    memset(padded_key, 0, KEY_SIZE);
    strncpy((char*)padded_key, key, KEY_SIZE);

    // Initialize encryption operation
    if(!EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, padded_key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    int data_len = strlen(data);
    int max_out_len = data_len + BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(max_out_len);
    if(!encrypted) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    int len1, len2;

    // Encrypt data
    if(!EVP_EncryptUpdate(ctx, encrypted, &len1, (unsigned char*)data, data_len)) {
        free(encrypted);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    // Finalize encryption
    if(!EVP_EncryptFinal_ex(ctx, encrypted + len1, &len2)) {
        free(encrypted);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    EVP_CIPHER_CTX_free(ctx);

    // Convert to base64
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, encrypted, len1 + len2);
    BIO_flush(b64);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(b64, &bptr);

    char* result = (char*)malloc(bptr->length);
    if(result) {
        memcpy(result, bptr->data, bptr->length - 1);
        result[bptr->length - 1] = '\0';
    }

    BIO_free_all(b64);
    free(encrypted);

    return result;
}

int main() {
    initialize();
    const char* key = "MySecretKey12345";

    // Test case 1: Normal string
    char* result = encrypt("Hello World", key);
    if(result) {
        printf("Test 1: %s\\n", result);
        free(result);
    }

    // Test case 2: Empty string
    result = encrypt("", key);
    if(result) {
        printf("Test 2: %s\\n", result);
        free(result);
    }

    // Test case 3: Long string
    result = encrypt("This is a very long string for testing encryption", key);
    if(result) {
        printf("Test 3: %s\\n", result);
        free(result);
    }

    // Test case 4: Special characters
    result = encrypt("!@#$%^&*()", key);
    if(result) {
        printf("Test 4: %s\\n", result);
        free(result);
    }

    // Test case 5: Numbers
    result = encrypt("1234567890", key);
    if(result) {
        printf("Test 5: %s\\n", result);
        free(result);
    }

    return 0;
}
