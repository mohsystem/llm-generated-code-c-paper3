#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>

void encrypt(const char *plaintext, char *encrypted_text) {
    unsigned char key[32];
    unsigned char iv[12];

    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        fprintf(stderr, "Failed to generate key or IV\n");
        return;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to create EVP_CIPHER_CTX\n");
        return;
    }

    int len;
    int ciphertext_len = 0;
    unsigned char ciphertext[128];

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) ||
        1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv) ||
        1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (const unsigned char *)plaintext, strlen(plaintext))) {
        EVP_CIPHER_CTX_free(ctx);
        fprintf(stderr, "Encryption failed\n");
        return;
    }
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        fprintf(stderr, "Final encryption step failed\n");
        return;
    }
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    memcpy(encrypted_text, iv, sizeof(iv));
    memcpy(encrypted_text + sizeof(iv), ciphertext, ciphertext_len);
}

int main() {
    char encrypted_text[128 + 12]; // IV + ciphertext
    encrypt("Hello, World!", encrypted_text);
    printf("%s\n", encrypted_text);
    encrypt("Test String", encrypted_text);
    printf("%s\n", encrypted_text);
    encrypt("Secure Encryption", encrypted_text);
    printf("%s\n", encrypted_text);
    encrypt("C Encryption", encrypted_text);
    printf("%s\n", encrypted_text);
    encrypt("Cryptographic Example", encrypted_text);
    printf("%s\n", encrypted_text);

    return 0;
}