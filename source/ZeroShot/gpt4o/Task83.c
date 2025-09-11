#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void encrypt(const char *plainText, const unsigned char *key, const unsigned char *iv, unsigned char *encrypted) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    int len;
    EVP_EncryptUpdate(ctx, encrypted, &len, (unsigned char *)plainText, strlen(plainText));
    
    int padding_len;
    EVP_EncryptFinal_ex(ctx, encrypted + len, &padding_len);
    len += padding_len;

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    unsigned char key[16];
    unsigned char iv[16];
    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    unsigned char encrypted[128];

    // Test cases
    encrypt("Test123", key, iv, encrypted);
    printf("%s\n", encrypted);
    encrypt("HelloWorld", key, iv, encrypted);
    printf("%s\n", encrypted);
    encrypt("CEncryption", key, iv, encrypted);
    printf("%s\n", encrypted);
    encrypt("SecureCode", key, iv, encrypted);
    printf("%s\n", encrypted);
    encrypt("CipherTest", key, iv, encrypted);
    printf("%s\n", encrypted);

    return 0;
}