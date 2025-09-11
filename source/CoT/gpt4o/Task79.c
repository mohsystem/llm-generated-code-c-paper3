#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void encrypt(const char *message, const char *key, unsigned char *output) {
    AES_KEY encryptKey;
    unsigned char iv[AES_BLOCK_SIZE];

    // Generate random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        fprintf(stderr, "Error generating random bytes for IV\n");
        return;
    }

    AES_set_encrypt_key((const unsigned char*)key, 128, &encryptKey);

    int num = 0;
    AES_cfb128_encrypt((const unsigned char*)message, output, strlen(message), &encryptKey, iv, &num, AES_ENCRYPT);
}

int main() {
    // Test cases
    const char *key = "0123456789abcdef"; // 16 bytes key for AES128
    unsigned char output[128];

    encrypt("Hello World", key, output);
    printf("%s\n", output);

    encrypt("C Encryption", key, output);
    printf("%s\n", output);

    encrypt("Secure Message", key, output);
    printf("%s\n", output);

    encrypt("Encrypt this text", key, output);
    printf("%s\n", output);

    encrypt("Sample Test", key, output);
    printf("%s\n", output);

    return 0;
}