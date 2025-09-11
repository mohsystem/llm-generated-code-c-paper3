#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

void encrypt(const char* message, const char* secret, char* output) {
    unsigned char key[32];
    SHA256((unsigned char*)secret, strlen(secret), key);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);

    int len = 0;
    int ciphertext_len = 0;
    unsigned char encrypted[128];

    EVP_EncryptUpdate(ctx, encrypted, &len, (unsigned char*)message, strlen(message));
    ciphertext_len += len;

    EVP_EncryptFinal_ex(ctx, encrypted + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    for (int i = 0; i < ciphertext_len; i++) {
        sprintf(output + (i * 2), "%02x", encrypted[i]);
    }
    output[ciphertext_len * 2] = '\0';
}

int main() {
    char output[256];
    const char* secret = "mysecretkey";

    encrypt("Hello, World!", secret, output);
    printf("%s\n", output);

    encrypt("Secure Message", secret, output);
    printf("%s\n", output);

    encrypt("C Encryption", secret, output);
    printf("%s\n", output);

    encrypt("Encrypt this text", secret, output);
    printf("%s\n", output);

    encrypt("Last test message", secret, output);
    printf("%s\n", output);

    return 0;
}