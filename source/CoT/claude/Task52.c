
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>

#define KEY_SIZE 32
#define BLOCK_SIZE 16
#define BUFFER_SIZE 1024

void generate_key(const char* password, unsigned char* key) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(key, &sha256);
}

void encrypt_file(const char* input_file, const char* output_file, const char* password) {
    unsigned char key[KEY_SIZE];
    generate_key(password, key);
    
    FILE* inFile = fopen(input_file, "rb");
    FILE* outFile = fopen(output_file, "wb");
    
    if (!inFile || !outFile) {
        if (inFile) fclose(inFile);
        if (outFile) fclose(outFile);
        return;
    }
    
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
    
    unsigned char inbuf[BUFFER_SIZE];
    unsigned char outbuf[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int outlen;
    size_t inlen;
    
    while ((inlen = fread(inbuf, 1, BUFFER_SIZE, inFile)) > 0) {
        EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, inlen);
        fwrite(outbuf, 1, outlen, outFile);
    }
    
    EVP_EncryptFinal_ex(ctx, outbuf, &outlen);
    fwrite(outbuf, 1, outlen, outFile);
    
    EVP_CIPHER_CTX_free(ctx);
    fclose(inFile);
    fclose(outFile);
}

void decrypt_file(const char* input_file, const char* output_file, const char* password) {
    unsigned char key[KEY_SIZE];
    generate_key(password, key);
    
    FILE* inFile = fopen(input_file, "rb");
    //todo    //incomplete code
    // FILE* outFile = fopen(output', type='text')
}