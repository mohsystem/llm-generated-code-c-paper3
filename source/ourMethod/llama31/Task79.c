#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/rand.h>

void print_hex(const unsigned char* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void encrypt(const unsigned char* message, size_t message_len, const unsigned char* key, unsigned char* encrypted) {
    unsigned char iv[16];
    RAND_bytes(iv, 16);

    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    // Copy IV to the beginning of the encrypted buffer
    memcpy(encrypted, iv, 16);

    AES_cbc_encrypt(message, encrypted + 16, message_len, &aes_key, iv, AES_ENCRYPT);
}

void decrypt(const unsigned char* encrypted, size_t encrypted_len, const unsigned char* key, unsigned char* decrypted) {
    if (encrypted_len < 16) {
        fprintf(stderr, "Invalid encrypted message\n");
        return;
    }

    unsigned char iv[16];
    memcpy(iv, encrypted, 16);

    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    AES_cbc_encrypt(encrypted + 16, decrypted, encrypted_len - 16, &aes_key, iv, AES_DECRYPT);
}

int main() {
    const char* secret_key = "your_secret_key_here"; // Ensure this is a secure key
    const char* message = "This is a secret message";

    size_t message_len = strlen(message);
    size_t encrypted_len = message_len + 16; // Add space for IV

    unsigned char* encrypted = malloc(encrypted_len);
    if (!encrypted) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    encrypt((const unsigned char*)message, message_len, (const unsigned char*)secret_key, encrypted);

    printf("Encrypted: ");
    print_hex(encrypted, encrypted_len);

    unsigned char* decrypted = malloc(message_len);
    if (!decrypted) {
        fprintf(stderr, "Memory allocation failed\n");
        free(encrypted);
        return 1;
    }

    decrypt(encrypted, encrypted_len, (const unsigned char*)secret_key, decrypted);

    printf("Decrypted: %s\n", decrypted);

    free(encrypted);
    free(decrypted);

    return 0;
}