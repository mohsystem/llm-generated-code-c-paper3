// Note: This requires OpenSSL library and base64 library
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>
#include <base64.h>

void encrypt(unsigned char* key, unsigned char* value, int value_len, unsigned char* encrypted) {
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);
    AES_set_encrypt_key(key, 128, &aes_key);

    AES_cbc_encrypt(value, encrypted, value_len, &aes_key, iv, AES_ENCRYPT);
}

int main() {
    unsigned char key[16] = "1234567812345678";
    unsigned char value[] = "This is a secret message";
    int value_len = strlen((char*)value);
    unsigned char encrypted[value_len];

    encrypt(key, value, value_len, encrypted);

    char* encoded = base64_encode(encrypted, value_len);
    printf("Encrypted: %s\n", encoded);
    free(encoded);

    return 0;
}