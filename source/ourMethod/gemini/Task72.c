#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>


static unsigned char IV[AES_BLOCK_SIZE];


unsigned char* pad_data(const unsigned char* data, size_t data_len, size_t* padded_data_len) {
    size_t padding_length = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    *padded_data_len = data_len + padding_length;
    unsigned char* padded_data = (unsigned char*)malloc(*padded_data_len);
    if (!padded_data) {
        return NULL;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_length, padding_length);
    return padded_data;
}

unsigned char* encrypt(const unsigned char* data, size_t data_len, const unsigned char* key, size_t key_len, size_t* encrypted_data_len) {

    if (key_len != 32) {
        fprintf(stderr, "Key length must be 32 bytes.\n");
        return NULL;
    }

    // Generate IV once
    if (!IV[0]) {
        if (RAND_bytes(IV, AES_BLOCK_SIZE) != 1) {
            fprintf(stderr, "Failed to generate IV.\n");
            return NULL;
        }
    }

    size_t padded_data_len;
    unsigned char* padded_data = pad_data(data, data_len, &padded_data_len);
    if (!padded_data) {
        return NULL;
    }

    unsigned char* encrypted_data = (unsigned char*)malloc(padded_data_len);

     EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(padded_data);
        fprintf(stderr, "Failed to create cipher context.\n");
        return NULL;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, IV) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(padded_data);
        fprintf(stderr, "Failed to initialize encryption.\n");
        return NULL;
    }


    int len;
    if (EVP_EncryptUpdate(ctx, encrypted_data, &len, padded_data, padded_data_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(padded_data);
        fprintf(stderr, "Failed to encrypt update.\n");
        return NULL;

    }

    int final_len;
    if (EVP_EncryptFinal_ex(ctx, encrypted_data + len, &final_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(padded_data);
        fprintf(stderr, "Failed to finalize encryption.\n");

        return NULL;

    }

    EVP_CIPHER_CTX_free(ctx);

    *encrypted_data_len = len + final_len;
    free(padded_data);
    return encrypted_data;
}



int main() {
    unsigned char key[] = "0123456789abcdef0123456789abcdef";
    size_t key_len = sizeof(key) -1 ;

    const char* test_cases[] = {
        "Test data 1",
        "Test data 2 slightly longer",
        "Short",
        "Special characters !@#$%^&*()_+=-`~[]\';,./{}|:\"<>?",
        "1234567890123456"
    };
    size_t num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_test_cases; ++i) {
        size_t data_len = strlen(test_cases[i]);
        size_t encrypted_data_len;

        unsigned char *encrypted_data = encrypt((const unsigned char*)test_cases[i], data_len, key, key_len, &encrypted_data_len);
        if (encrypted_data) {
            printf("Encrypted Data %zu: ", i + 1);
            for (size_t j = 0; j < encrypted_data_len; ++j) {
                printf("%02x", encrypted_data[j]);
            }
            printf("\n");
            free(encrypted_data);
        }
    }

    return 0;
}