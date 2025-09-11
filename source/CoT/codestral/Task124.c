// This code requires OpenSSL library.
// Compile with: gcc -lcrypto file.c
#include <stdio.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <string.h>

typedef struct {
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
} Task124;

void Task124_init(Task124* t, const char* keyStr) {
    memset(t->key, 0, sizeof t->key);
    memset(t->iv, 0, sizeof t->iv);
    strncpy(t->key, keyStr, EVP_MAX_KEY_LENGTH);
}

void Task124_encrypt(Task124* t, const char* data, char* encryptedData) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, t->key, t->iv);
    int len = strlen(data);
    int c_len = len + AES_BLOCK_SIZE;
    unsigned char* ciphertext = malloc(c_len);
    EVP_EncryptUpdate(ctx, ciphertext, &c_len, data, len);
    int final_len = 0;
    EVP_EncryptFinal_ex(ctx, ciphertext + c_len, &final_len);
    EVP_CIPHER_CTX_free(ctx);
    memcpy(encryptedData, ciphertext, c_len + final_len);
    free(ciphertext);
}

void Task124_decrypt(Task124* t, const char* encryptedData, char* data) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, t->key, t->iv);
    int len = strlen(encryptedData);
    int p_len = len;
    unsigned char* plaintext = malloc(p_len);
    EVP_DecryptUpdate(ctx, plaintext, &p_len, encryptedData, len);
    int final_len = 0;
    EVP_DecryptFinal_ex(ctx, plaintext + p_len, &final_len);
    EVP_CIPHER_CTX_free(ctx);
    memcpy(data, plaintext, p_len + final_len);
    free(plaintext);
}

int main() {
    Task124 t;
    Task124_init(&t, "MySecretKey12345");
    char data[100] = "Sensitive information";
    char encryptedData[100];
    Task124_encrypt(&t, data, encryptedData);
    printf("Encrypted data: %s\n", encryptedData);
    char decryptedData[100];
    Task124_decrypt(&t, encryptedData, decryptedData);
    printf("Decrypted data: %s\n", decryptedData);
    return 0;
}