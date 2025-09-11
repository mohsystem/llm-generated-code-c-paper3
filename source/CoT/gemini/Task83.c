#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>


// Helper function for Base64 encoding (using OpenSSL)
char* base64_encode(const unsigned char* input, int length) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *result = (char *)malloc(bptr->length + 1);
    memcpy(result, bptr->data, bptr->length);
    result[bptr->length] = '\0';
    BIO_free_all(b64);
    return result;
}



char *encrypt(const char *key_to_encrypt) {
    // Generate a secure random 128-bit key for AES
    unsigned char key[16];
    RAND_bytes(key, 16);


    // Generate a random IV (Initialization Vector)
    unsigned char iv[16];
    RAND_bytes(iv, 16);


    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    // Calculate padded length
    int input_length = strlen(key_to_encrypt);
    int padding_length = AES_BLOCK_SIZE - (input_length % AES_BLOCK_SIZE);
    int padded_length = input_length + padding_length;


    unsigned char *padded_key = (unsigned char *)malloc(padded_length);
    memcpy(padded_key, key_to_encrypt, input_length);
    for (int i = 0; i < padding_length; i++) {
        padded_key[input_length + i] = padding_length;
    }

    unsigned char *encrypted_data = (unsigned char *)malloc(padded_length);
    AES_cbc_encrypt(padded_key, encrypted_data, padded_length, &aes_key, iv, AES_ENCRYPT);


    unsigned char *combined = (unsigned char *)malloc(16 + padded_length);
    memcpy(combined, iv, 16);
    memcpy(combined + 16, encrypted_data, padded_length);

    char *base64_encrypted = base64_encode(combined, 16 + padded_length);


    free(padded_key);
    free(encrypted_data);
    free(combined);


    return base64_encrypted;
}


int main() {
    char *test_cases[] = {"test1", "test2_longer", "test3_with_special_!@#", "test4_1234567890", ""};
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        char *encrypted = encrypt(test_cases[i]);
        printf("Encrypted: %s\n", encrypted);
        free(encrypted); // Free allocated memory
    }

    return 0;
}