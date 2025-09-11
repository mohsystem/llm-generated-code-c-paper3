// This code requires OpenSSL library
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>
#include <base64.h>

char* encrypt(const char* message, const char* secretKey) {
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    int iv_len = EVP_CIPHER_iv_length(EVP_aes_256_cfb());
    RAND_bytes(iv, iv_len);
    EVP_BytesToKey(EVP_aes_256_cfb(), EVP_sha256(), nullptr, (const unsigned char*)secretKey, strlen(secretKey), 1, key, iv);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), nullptr, key, iv);

    int len = 0, ciphertext_len = 0;
    unsigned char ciphertext[strlen(message) + EVP_MAX_BLOCK_LENGTH];
    EVP_EncryptUpdate(ctx, ciphertext, &len, (const unsigned char*)message, strlen(message));
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    char* encryptedMessage = (char*)malloc(ciphertext_len + 1);
    memcpy(encryptedMessage, ciphertext, ciphertext_len);
    encryptedMessage[ciphertext_len] = '\0';

    return base64_encode(encryptedMessage);
}

int main() {
    const char* message = "Hello, World!";
    const char* secretKey = "MySecretKey";
    char* encryptedMessage = encrypt(message, secretKey);
    printf("Encrypted message: %s\n", encryptedMessage);
    free(encryptedMessage);
    return 0;
}