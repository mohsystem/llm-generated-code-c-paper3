#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void handleErrors(void) {
    fprintf(stderr, "Error occurred\n");
    exit(EXIT_FAILURE);
}

void encrypt_decrypt(const unsigned char *input, int input_len, unsigned char *key, unsigned char *output, int encrypt) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;

    if (!ctx) handleErrors();

    if (encrypt) {
        if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, key, NULL))
            handleErrors();
        if (1 != EVP_EncryptUpdate(ctx, output, &len, input, input_len))
            handleErrors();
    } else {
        if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, key, NULL))
            handleErrors();
        if (1 != EVP_DecryptUpdate(ctx, output, &len, input, input_len))
            handleErrors();
    }

    EVP_CIPHER_CTX_free(ctx);
}

int main(void) {
    unsigned char key[32];
    if (1 != RAND_bytes(key, sizeof(key)))
        handleErrors();

    unsigned char *input = (unsigned char *)"This is a test.";
    unsigned char output[128];
    unsigned char decrypted_output[128];

    encrypt_decrypt(input, strlen((char *)input), key, output, 1);
    printf("Encrypted data: %s\n", output);

    encrypt_decrypt(output, strlen((char *)input), key, decrypted_output, 0);
    printf("Decrypted data: %s\n", decrypted_output);

    return 0;
}