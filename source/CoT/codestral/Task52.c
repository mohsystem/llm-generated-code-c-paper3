// C code:
#include <stdio.h>
#include <openssl/aes.h>

void encrypt(const char* inputFile, const char* outputFile, const unsigned char* key) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 256, &aesKey);

    FILE* input = fopen(inputFile, "rb");
    FILE* output = fopen(outputFile, "wb");

    unsigned char in[AES_BLOCK_SIZE], out[AES_BLOCK_SIZE];

    while (fread(in, 1, AES_BLOCK_SIZE, input) == AES_BLOCK_SIZE) {
        AES_encrypt(in, out, &aesKey);
        fwrite(out, 1, AES_BLOCK_SIZE, output);
    }

    fclose(input);
    fclose(output);
}

void decrypt(const char* inputFile, const char* outputFile, const unsigned char* key) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 256, &aesKey);

    FILE* input = fopen(inputFile, "rb");
    FILE* output = fopen(outputFile, "wb");

    unsigned char in[AES_BLOCK_SIZE], out[AES_BLOCK_SIZE];

    while (fread(in, 1, AES_BLOCK_SIZE, input) == AES_BLOCK_SIZE) {
        AES_decrypt(in, out, &aesKey);
        fwrite(out, 1, AES_BLOCK_SIZE, output);
    }

    fclose(input);
    fclose(output);
}

int main() {
    unsigned char key[32] = { 0 }; // 32 bytes for 256-bit key

    encrypt("input.txt", "encrypted.txt", key);
    decrypt("encrypted.txt", "decrypted.txt", key);

    return 0;
}