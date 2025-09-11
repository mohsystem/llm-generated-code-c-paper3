
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* encrypt(const char* message, const char* secret_key) {
    if (!message || !secret_key) {
        return strdup("Encryption failed: NULL input");
    }

    // Prepare key
    unsigned char key[32];
    memset(key, 0, sizeof(key));
    size_t keylen = strlen(secret_key);
    memcpy(key, secret_key, keylen > 32 ? 32 : keylen);

    // Initialize context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        return strdup("Encryption failed: Context creation failed");
    }

    // Initialize encryption
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return strdup("Encryption failed: Initialization failed");
    }

    // Prepare output buffer
    int message_len = strlen(message);
    int cipher_len = message_len + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = (unsigned char*)malloc(cipher_len);
    if (!ciphertext) {
        EVP_CIPHER_CTX_free(ctx);
        return strdup("Encryption failed: Memory allocation failed");
    }

    // Encrypt
    int len1, len2;
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len1, 
                              (unsigned char*)message, message_len)) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return strdup("Encryption failed: Encryption update failed");
    }

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len1, &len2)) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return strdup("Encryption failed: Encryption finalization failed");
    }

    // Base64 encode
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, ciphertext, len1 + len2);
    BIO_flush(b64);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(b64, &bptr);

    char* result = (char*)malloc(bptr->length + 1);
    if (!result) {
        free(ciphertext);
        BIO_free_all(b64);
        EVP_CIPHER_CTX_free(ctx);
        return strdup("Encryption failed: Memory allocation failed");
    }

    memcpy(result, bptr->data, bptr->length);
    result[bptr->length - 1] = '\\0';  // Remove newline added by base64

    // Clean up
    free(ciphertext);
    BIO_free_all(b64);
    EVP_CIPHER_CTX_free(ctx);

    return result;
}

int main() {
    const char* key = "MySecretKey12345";
    
    char* result1 = encrypt("Hello World!", key);
    printf("Test 1: %s\\n", result1);
    free(result1);

    char* result2 = encrypt("Secret Message", key);
    printf("Test 2: %s\\n", result2);
    free(result2);

    char* result3 = encrypt("12345", key);
    printf("Test 3: %s\\n", result3);
    free(result3);

    char* result4 = encrypt("Special @#$%", key);
    printf("Test 4: %s\\n", result4);
    free(result4);

    char* result5 = encrypt("", key);
    printf("Test 5: %s\\n", result5);
    free(result5);

    return 0;
}
