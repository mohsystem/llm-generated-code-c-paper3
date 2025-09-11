// The provided code snippet for C is a simplified version and doesn't include the base64 encoding.
// Adding base64 encoding would require additional libraries or custom implementation, which is beyond the scope of this response.
// Therefore, the output of the encryption is presented as raw bytes.

#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

void encrypt(const char* input, const char* key, unsigned char* output) {
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0, AES_BLOCK_SIZE);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)key, iv);

    int len;
    int ciphertext_len;

    EVP_EncryptUpdate(ctx, output, &len, (const unsigned char*)input, strlen(input));
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, output + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    const char* key = "1234567890123456";
    const char* input = "Hello World!";
    unsigned char output[128];

    encrypt(input, key, output);

    for (int i = 0; i < 16; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");

    return 0;
}