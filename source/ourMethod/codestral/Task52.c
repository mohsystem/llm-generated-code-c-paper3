#include <stdio.h>
#include <stdint.h>
#include <openssl/aes.h>

const uint8_t KEY[] = "1234567890123456";

void encrypt(const char* inputFile, const char* outputFile) {
    FILE* input = fopen(inputFile, "rb");
    FILE* output = fopen(outputFile, "wb");

    AES_KEY aesKey;
    AES_set_encrypt_key(KEY, 128, &aesKey);

    uint8_t in[AES_BLOCK_SIZE];
    uint8_t out[AES_BLOCK_SIZE];

    while (fread(in, 1, AES_BLOCK_SIZE, input) == AES_BLOCK_SIZE) {
        AES_encrypt(in, out, &aesKey);
        fwrite(out, 1, AES_BLOCK_SIZE, output);
    }

    fclose(input);
    fclose(output);
}

void decrypt(const char* inputFile, const char* outputFile) {
    FILE* input = fopen(inputFile, "rb");
    FILE* output = fopen(outputFile, "wb");

    AES_KEY aesKey;
    AES_set_decrypt_key(KEY, 128, &aesKey);

    uint8_t in[AES_BLOCK_SIZE];
    uint8_t out[AES_BLOCK_SIZE];

    while (fread(in, 1, AES_BLOCK_SIZE, input) == AES_BLOCK_SIZE) {
        AES_decrypt(in, out, &aesKey);
        fwrite(out, 1, AES_BLOCK_SIZE, output);
    }

    fclose(input);
    fclose(output);
}

int main() {
    encrypt("plaintext.txt", "encrypted.txt");
    decrypt("encrypted.txt", "decrypted.txt");
    return 0;
}