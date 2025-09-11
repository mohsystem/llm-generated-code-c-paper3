#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>

void aes_cbc_encrypt(const unsigned char *key, const unsigned char *iv, const unsigned char *plaintext, unsigned char *ciphertext, size_t plaintext_len) {
    AES_KEY encryptKey;
    AES_set_encrypt_key(key, 128, &encryptKey);

    for (size_t i = 0; i < plaintext_len; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(plaintext + i, ciphertext + i, AES_BLOCK_SIZE, &encryptKey, const_cast<unsigned char*>(iv), AES_ENCRYPT);
    }
}

int main() {
    unsigned char key[AES_BLOCK_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char plaintext[] = "This is a test message.";
    size_t plaintext_len = strlen((char*)plaintext);
    size_t ciphertext_len = ((plaintext_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char ciphertext[ciphertext_len];

    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    aes_cbc_encrypt(key, iv, plaintext, ciphertext, plaintext_len);

    printf("Encrypted: ");
    for (size_t i = 0; i < ciphertext_len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}