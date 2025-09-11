#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void handleErrors() {
    fprintf(stderr, "An error occurred.\n");
    exit(1);
}

unsigned char* generateKey() {
    unsigned char *key = (unsigned char*) malloc(EVP_MAX_KEY_LENGTH);
    if (!RAND_bytes(key, EVP_MAX_KEY_LENGTH)) {
        handleErrors();
    }
    return key;
}

void encryptFile(const char *inputFile, const char *outputFile, unsigned char *key) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    unsigned char iv[EVP_MAX_IV_LENGTH];
    if (!RAND_bytes(iv, EVP_MAX_IV_LENGTH)) handleErrors();

    FILE *ifp = fopen(inputFile, "rb");
    FILE *ofp = fopen(outputFile, "wb");

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) handleErrors();
    
    fwrite(iv, 1, sizeof(iv), ofp);

    unsigned char buffer[1024];
    unsigned char ciphertext[1024 + EVP_CIPHER_CTX_block_size(ctx)];

    int len;
    int bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), ifp)) > 0) {
        if (!EVP_EncryptUpdate(ctx, ciphertext, &len, buffer, bytesRead)) handleErrors();
        fwrite(ciphertext, 1, len, ofp);
    }

    if (!EVP_EncryptFinal_ex(ctx, ciphertext, &len)) handleErrors();
    fwrite(ciphertext, 1, len, ofp);

    EVP_CIPHER_CTX_free(ctx);
    fclose(ifp);
    fclose(ofp);
}

void decryptFile(const char *inputFile, const char *outputFile, unsigned char *key) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    FILE *ifp = fopen(inputFile, "rb");
    FILE *ofp = fopen(outputFile, "wb");

    unsigned char iv[EVP_MAX_IV_LENGTH];
    fread(iv, 1, sizeof(iv), ifp);

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) handleErrors();

    unsigned char buffer[1024];
    unsigned char plaintext[1024 + EVP_CIPHER_CTX_block_size(ctx)];

    int len;
    int bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), ifp)) > 0) {
        if (!EVP_DecryptUpdate(ctx, plaintext, &len, buffer, bytesRead)) handleErrors();
        fwrite(plaintext, 1, len, ofp);
    }

    if (!EVP_DecryptFinal_ex(ctx, plaintext, &len)) handleErrors();
    fwrite(plaintext, 1, len, ofp);

    EVP_CIPHER_CTX_free(ctx);
    fclose(ifp);
    fclose(ofp);
}

int main() {
    unsigned char *key = generateKey();
    const char *inputFile = "test_input.txt";
    const char *encryptedFile = "test_encrypted.txt";
    const char *decryptedFile = "test_decrypted.txt";

    // Writing test data
    FILE *input = fopen(inputFile, "w");
    fputs("Test Data", input);
    fclose(input);

    // Test Cases
    encryptFile(inputFile, encryptedFile, key);
    decryptFile(encryptedFile, decryptedFile, key);

    free(key);
    printf("Encryption and Decryption completed.\n");
    return 0;
}