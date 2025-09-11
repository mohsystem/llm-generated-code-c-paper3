
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#define KEY_SIZE 32  // 256 bits
#define IV_SIZE 16   // 128 bits
#define MAX_BUFFER_SIZE 1024

typedef struct {
    unsigned char* data;
    size_t length;
} ByteArray;

// Function to generate random bytes
static ByteArray generate_random_bytes(size_t length) {
    ByteArray result = {NULL, 0};
    
    result.data = (unsigned char*)malloc(length);
    if (!result.data) {
        return result;
    }
    
    if (RAND_bytes(result.data, length) != 1) {
        free(result.data);
        result.data = NULL;
        return result;
    }
    
    result.length = length;
    return result;
}

// Function to perform base64 encoding
static char* base64_encode(const unsigned char* input, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    char* result = NULL;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    result = (char*)malloc(bufferPtr->length + 1);
    if (result) {
        memcpy(result, bufferPtr->data, bufferPtr->length);
        result[bufferPtr->length] = '\\0';
    }

    BIO_free_all(bio);
    return result;
}

char* encrypt_aes_cbc(const char* key) {
    if (!key || strlen(key) == 0) {
        return NULL;
    }

    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();

    // Generate random key and IV
    ByteArray aes_key = generate_random_bytes(KEY_SIZE);
    ByteArray iv = generate_random_bytes(IV_SIZE);
    
    if (!aes_key.data || !iv.data) {
        if (aes_key.data) free(aes_key.data);
        if (iv.data) free(iv.data);
        return NULL;
    }

    // Create and initialize context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(aes_key.data);
        free(iv.data);
        return NULL;
    }

    // Initialize encryption operation
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key.data, iv.data) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(aes_key.data);
        free(iv.data);
        return NULL;
    }

    // Prepare output buffer
    size_t key_len = strlen(key);
    unsigned char* ciphertext = (unsigned char*)malloc(key_len + EVP_MAX_BLOCK_LENGTH);
    int len1, len2;

    // Encrypt
    if (!ciphertext || 
        EVP_EncryptUpdate(ctx, ciphertext, &len1, (unsigned char*)key, key_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(aes_key.data);
        free(iv.data);
        if (ciphertext) free(ciphertext);
        return NULL;
    }

    // Finalize encryption
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len1, &len2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(aes_key.data);
        free(iv.data);
        free(ciphertext);
        return NULL;
    }

    // Combine IV and ciphertext
    size_t total_len = IV_SIZE + len1 + len2;
    unsigned char* result = (unsigned char*)malloc(total_len);
    if (!result) {
        EVP_CIPHER_CTX_free(ctx);
        free(aes_key.data);
        free(iv.data);
        free(ciphertext);
        return NULL;
    }

    memcpy(result, iv.data, IV_SIZE);
    memcpy(result + IV_SIZE, ciphertext, len1 + len2);

    // Convert to base64
    char* encoded = base64_encode(result, total_len);

    // Cleanup
    EVP_CIPHER_CTX_free(ctx);
    free(aes_key.data);
    free(iv.data);
    free(ciphertext);
    free(result);

    return encoded;
}

int main() {
    const char* test_cases[] = {
        "MySecretKey123",
        "AnotherKey456",
        "TestKey789",
        "SecurePassword",
        "EncryptThis!"
    };
    
    for (int i = 0; i < 5; i++) {
        char* encrypted = encrypt_aes_cbc(test_cases[i]);
        if (encrypted) {
            printf("Input: %s\\n", test_cases[i]);
            printf("Encrypted: %s\\n\\n", encrypted);
            free(encrypted);
        } else {
            printf("Encryption failed for: %s\\n", test_cases[i]);
        }
    }

    return 0;
}
