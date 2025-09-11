#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/rand.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {
    unsigned char key[16] = "0123456789abcdef";  // 16 bytes (128 bits) key
    unsigned char iv[16];
    if (RAND_bytes(iv, 16) != 1) {  // Random initialization vector
        handleErrors();
    }

    unsigned char plaintext[] = "This is a secret message";
    int plaintext_len = strlen((char*)plaintext);

    // Encryption
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 128, &aesKey) != 0) {
        handleErrors();
    }

    int ciphertext_len = ((plaintext_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    unsigned char* ciphertext = malloc(ciphertext_len);
    if (!ciphertext) {
        handleErrors();
    }

    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aesKey, iv, AES_ENCRYPT);

    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted: ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Decryption
    if (AES_set_decrypt_key(key, 128, &aesKey) != 0) {
        handleErrors();
    }

    unsigned char* decrypted = malloc(ciphertext_len);
    if (!decrypted) {
        handleErrors();
    }

    AES_cbc_encrypt(ciphertext, decrypted, ciphertext_len, &aesKey, iv, AES_DECRYPT);

    printf("Decrypted: %s\n", decrypted);

    free(ciphertext);
    free(decrypted);

    return 0;
}