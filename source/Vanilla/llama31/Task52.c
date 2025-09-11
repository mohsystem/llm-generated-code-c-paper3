#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void encryptFile(const char* input_file, const char* output_file, unsigned char* key) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    FILE* ifs = fopen(input_file, "rb");
    FILE* ofs = fopen(output_file, "wb");
    unsigned char iv[16];
    fread(iv, 1, 16, ifs);
    unsigned char buffer[16];
    while (fread(buffer, 1, 16, ifs) == 16) {
        unsigned char encrypted[16];
        AES_cbc_encrypt(buffer, encrypted, 16, &aes_key, iv, AES_ENCRYPT);
        fwrite(encrypted, 1, 16, ofs);
    }
    fclose(ifs);
    fclose(ofs);
}

void decryptFile(const char* input_file, const char* output_file, unsigned char* key) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    FILE* ifs = fopen(input_file, "rb");
    FILE* ofs = fopen(output_file, "wb");
    unsigned char iv[16];
    fread(iv, 1, 16, ifs);
    unsigned char buffer[16];
    while (fread(buffer, 1, 16, ifs) == 16) {
        unsigned char decrypted[16];
        AES_cbc_encrypt(buffer, decrypted, 16, &aes_key, iv, AES_DECRYPT);
        fwrite(decrypted, 1, 16, ofs);
    }
    fclose(ifs);
    fclose(ofs);
}

void testCases(unsigned char* key) {
    for (int i = 0; i < 5; i++) {
        char input_file[256];
        char encrypted_file[256];
        char decrypted_file[256];
        sprintf(input_file, "test%d.txt", i+1);
        sprintf(encrypted_file, "test%d_enc.txt", i+1);
        sprintf(decrypted_file, "test%d_dec.txt", i+1);
        encryptFile(input_file, encrypted_file, key);
        decryptFile(encrypted_file, decrypted_file, key);
    }
}

int main() {
    unsigned char key[16];
    // Initialize key with some value, for example:
    for (int i = 0; i < 16; i++) {
        key[i] = i;
    }
    testCases(key);
    return 0;
}