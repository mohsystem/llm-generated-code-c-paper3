#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void encrypt(const char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int *ciphertext_len) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)plaintext, strlen(plaintext));
    *ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    *ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

void decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, char *plaintext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, plaintext_len;

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, (unsigned char *)plaintext, &len, ciphertext, ciphertext_len);
    plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, (unsigned char *)plaintext + len, &len);
    plaintext_len += len;
    plaintext[plaintext_len] = '\0';

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    // Generate key and IV for testing
    unsigned char key[EVP_MAX_KEY_LENGTH] = "01234567890123456789012345678901";
    unsigned char iv[EVP_MAX_IV_LENGTH] = "0123456789012345";

    // Test cases
    const char* test_cases[] = {
        "Hello World!",
        "Java Programming",
        "1234567890",
        "Encrypt this text",
        "Final Test Case"
    };

    unsigned char encrypted[128];
    char decrypted[128];
    int encrypted_len;

    for (int i = 0; i < 5; i++) {
        encrypt(test_cases[i], key, iv, encrypted, &encrypted_len);
        decrypt(encrypted, encrypted_len, key, iv, decrypted);

        printf("Original: %s\n", test_cases[i]);
        printf("Encrypted: %.*s\n", encrypted_len, encrypted);
        printf("Decrypted: %s\n\n", decrypted);
    }

    return 0;
}