
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define KEY_SIZE 32  // 256 bits
#define BUFFER_SIZE 1024

typedef struct {
    unsigned char key[KEY_SIZE];
} EncryptionKey;

void generate_key(EncryptionKey* key) {
    if (!RAND_bytes(key->key, KEY_SIZE)) {
        fprintf(stderr, "Failed to generate secure key\\n");
        exit(1);
    }
}

void encrypt_file(const char* input_file, const char* output_file, const EncryptionKey* key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to create cipher context\\n");
        exit(1);
    }

    // Initialize encryption operation
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key->key, NULL) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        fprintf(stderr, "Failed to initialize encryption\\n");
        exit(1);
    }

    FILE* in_fp = fopen(input_file, "rb");
    FILE* out_fp = fopen(output_file, "wb");
    
    if (!in_fp || !out_fp) {
        EVP_CIPHER_CTX_free(ctx);
        fprintf(stderr, "Failed to open files\\n");
        exit(1);
    }

    unsigned char in_buf[BUFFER_SIZE];
    unsigned char out_buf[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int out_len;
    size_t read_len;

    while ((read_len = fread(in_buf, 1, BUFFER_SIZE, in_fp)) > 0) {
        if (EVP_EncryptUpdate(ctx, out_buf, &out_len, in_buf, rea', type='text')