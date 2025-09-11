
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Base64 encoding table
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const unsigned char* data, int input_length) {
    int output_length = 4 * ((input_length + 2) / 3);
    char* encoded_data = malloc(output_length + 1);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_table[triple & 0x3F];
    }

    int mod_table[] = {0, 2, 1};
    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[output_length - 1 - i] = '=';

    encoded_data[output_length] = '\\0';
    return encoded_data;
}

char* encrypt_aes(const char* plaintext, const char* key) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) return NULL;

    unsigned char key_data[16];
    memset(key_data, 0, sizeof(key_data));
    memcpy(key_data, key, strlen(key) < 16 ? strlen(key) : 16);

    unsigned char iv[16] = {0}; // Initialize IV with zeros

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key_data, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    int len = strlen(plaintext);
    int c_len = len + AES_BLOCK_SIZE;
    int f_len = 0;
    unsigned char* ciphertext = malloc(c_len);
    
    if(!ciphertext) {
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &c_len, (unsigned char*)plaintext, len)) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + c_len, &f_len)) {
        free(ciphertext);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    EVP_CIPHER_CTX_free(ctx);
    
    char* result = base64_encode(ciphertext, c_len + f_len);
    free(ciphertext);
    
    return result;
}

int main() {
    const char* key = "ThisIsA16ByteKey";
    char* result;

    // Test cases
    result = encrypt_aes("Hello World", key);
    printf("Test 1: %s\\n", result ? result : "Error");
    free(result);

    result = encrypt_aes("SecretMessage123", key);
    printf("Test 2: %s\\n", result ? result : "Error");
    free(result);

    result = encrypt_aes("Testing AES CBC", key);
    printf("Test 3: %s\\n", result ? result : "Error");
    free(result);

    result = encrypt_aes("Confidential Data", key);
    printf("Test 4: %s\\n", result ? result : "Error");
    free(result);

    result = encrypt_aes("AES Encryption Test", key);
    printf("Test 5: %s\\n", result ? result : "Error");
    free(result);

    return 0;
}
