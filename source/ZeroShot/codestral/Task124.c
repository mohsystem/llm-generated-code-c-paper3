// This code uses the OpenSSL library.
// You can install it on Ubuntu using the command: sudo apt-get install libssl-dev
#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>

void encrypt(const char* data, char* encrypted_data) {
    const unsigned char key[] = "0123456789abcdef";
    unsigned char iv[AES_BLOCK_SIZE];
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        iv[i] = 0;
    }

    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);

    AES_cbc_encrypt(data, encrypted_data, strlen(data), &enc_key, iv, AES_ENCRYPT);
}

void decrypt(const char* encrypted_data, char* decrypted_data) {
    const unsigned char key[] = "0123456789abcdef";
    unsigned char iv[AES_BLOCK_SIZE];
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        iv[i] = 0;
    }

    AES_KEY dec_key;
    AES_set_decrypt_key(key, 128, &dec_key);

    AES_cbc_encrypt(encrypted_data, decrypted_data, strlen(encrypted_data), &dec_key, iv, AES_DECRYPT);
}

int main() {
    const char* data = "Sensitive data";
    char encrypted_data[100];
    char decrypted_data[100];

    encrypt(data, encrypted_data);
    decrypt(encrypted_data, decrypted_data);

    printf("%s\n", decrypted_data);

    return 0;
}