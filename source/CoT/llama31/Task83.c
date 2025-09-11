#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>

void aes_cbc_encrypt(const unsigned char *key, const unsigned char *iv, const unsigned char *plaintext, unsigned char *ciphertext, size_t plaintext_len) {
    AES_KEY encryptKey;
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &encryptKey, const_cast<unsigned char*>(iv), AES_ENCRYPT);
}

int main() {
    // Test cases
    unsigned char key[16]; // 128-bit key
    unsigned char iv[16]; // Initialization Vector
    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    const char* plaintexts[] = {
        "This is a test message.",
        "Another test message.",
        "Hello, AES!",
        "Encrypt me!",
        "Secure data here."
    };

    for (const char* plaintext : plaintexts) {
        size_t plaintext_len = strlen(plaintext);
        size_t ciphertext_len = ((plaintext_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Padding
        unsigned char ciphertext[ciphertext_len];
        aes_cbc_encrypt(key, iv, (const unsigned char*)plaintext, ciphertext, plaintext_len);
        printf("Plaintext: %s\n", plaintext);
        printf("Ciphertext: ");
        for (size_t i = 0; i < ciphertext_len; ++i) {
            printf("%02x", ciphertext[i]);
        }
        printf("\n");
    }

    return 0;
}