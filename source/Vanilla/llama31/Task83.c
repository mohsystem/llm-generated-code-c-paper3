#include <mbedtls/aes.h>
#include <stdio.h>
#include <string.h>

void encrypt_aes_cbc(unsigned char* key, unsigned char* iv, unsigned char* input, size_t input_len, unsigned char* output) {
    mbedtls_aes_context aes;
    mbedtls_aes_setkey_enc(&aes, key, 256);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 16, iv, input, output);
}

int main() {
    unsigned char key[32] = "0123456789abcdef";
    unsigned char iv[16] = "fedcba9876543210";
    unsigned char input[16] = "Hello, World!";
    unsigned char output[16];

    // Pad the input to a multiple of the block size (16 bytes for AES)
    size_t input_len = strlen((char*)input);
    size_t padded_len = (input_len + 15) / 16 * 16;
    unsigned char padded_input[padded_len];
    memcpy(padded_input, input, input_len);
    for (size_t i = input_len; i < padded_len; ++i) {
        padded_input[i] = padded_len - input_len;
    }

    encrypt_aes_cbc(key, iv, padded_input, padded_len, output);
    for (size_t i = 0; i < padded_len; ++i) {
        printf("%02x", output[i]);
    }
    printf("\n");

    return 0;
}