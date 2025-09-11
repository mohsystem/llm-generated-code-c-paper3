#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>

void encryptAES(const char* key) {
    unsigned char secretKey[32]; // 256-bit key
    unsigned char iv[16]; // AES block size
    unsigned char encrypted[1024];

    RAND_bytes(secretKey, sizeof(secretKey));
    RAND_bytes(iv, sizeof(iv));

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, secretKey, iv);

    int len;
    EVP_EncryptUpdate(ctx, encrypted, &len, (unsigned char*)key, strlen(key));

    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, encrypted + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x", encrypted[i]);
    }
    printf("\n");
}

int main() {
    encryptAES("testKey1");
    encryptAES("testKey2");
    encryptAES("testKey3");
    encryptAES("testKey4");
    encryptAES("testKey5");
    return 0;
}