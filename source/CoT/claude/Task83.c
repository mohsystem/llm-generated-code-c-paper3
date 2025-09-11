
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

// Function to encode data to base64
char* base64_encode(const unsigned char* input, int length) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char* buff = (char*)malloc(bptr->length);
    memcpy(buff, bptr->data, bptr->length-1);
    buff[bptr->length-1] = 0;

    BIO_free_all(b64);

    return buff;
}

// Function to encrypt key
char* encrypt_key(const char* key_to_encrypt, const char* secret_key) {
    if (!key_to_encrypt || !secret_key) {
        return NULL;
    }

    if (strlen(secret_key) != 16) {
        return NULL;
    }

    unsigned char iv[16];
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        return NULL;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        return NULL;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, 
        (unsigned char*)secret_key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    int key_len = strlen(key_to_encrypt);
    int cipher_len = key_len + EVP_MAX_BLOCK_LENGTH;
    unsigned char* encrypted = (unsigned char*)malloc(cipher_len);
    int outlen1, outlen2;

    if (EVP_EncryptUpdate(ctx, encrypted, &outlen1,
        (unsigned char*)key_to_encrypt, key_len) != 1) {
        free(encrypted);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    if (EVP_EncryptFinal_ex(ctx, encrypted + outlen1, &outlen2) != 1) {
        free(encrypted);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    EVP_CIPHER_CTX_free(ctx);

    // Combine IV and encrypted data
    int total_len = 16 + outlen1 + outlen2;
    unsigned char* result = (unsigned char*)malloc(total_len);
    memcpy(result, iv, 16);
    memcpy(result + 16, encrypted, outlen1 + outlen2);
    free(encrypted);

    char* base64_result = base64_encode(result, total_len);
    free(result);

    return base64_result;
}

int main() {
    const char* secret_key = "1234567890123456"; // 16-byte key

    // Test case 1: Normal input
    char* result1 = encrypt_key("Hello World!", secret_key);
    printf("Test 1: %s\\n", result1 ? result1 : "Error");
    free(result1);

    // Test case 2: Empty string
    char* result2 = encrypt_key("", secret_key);
    printf("Test 2: %s\\n", result2 ? result2 : "Error");
    free(result2);

    // Test case 3: Special characters
    char* result3 = encrypt_key("!@#$%^&*()", secret_key);
    printf("Test 3: %s\\n", result3 ? result3 : "Error");
    free(result3);

    // Test case 4: Long string
    char* result4 = encrypt_key("This is a very long string to encrypt", secret_key);
    printf("Test 4: %s\\n", result4 ? result4 : "Error");
    free(result4);

    // Test case 5: Numbers only
    char* result5 = encrypt_key("123456789", secret_key);
    printf("Test 5: %s\\n", result5 ? result5 : "Error");
    free(result5);

    return 0;
}
