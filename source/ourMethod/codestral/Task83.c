#include <stdio.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <base64.h>

char* encryptAES(const char* key) {
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    AES_KEY enc_key;
    unsigned char userKey[AES_BLOCK_SIZE];
    memset(userKey, 0, AES_BLOCK_SIZE);
    strncpy((char*)userKey, key, AES_BLOCK_SIZE);
    AES_set_encrypt_key(userKey, 128, &enc_key);

    unsigned char out[strlen(key) + AES_BLOCK_SIZE];
    AES_cbc_encrypt((unsigned char*)key, out, strlen(key), &enc_key, iv, AES_ENCRYPT);

    char* encoded = base64_encode(out, strlen(key));
    return encoded;
}

int main() {
    const char* key = "This is a secret";
    char* encryptedKey = encryptAES(key);
    printf("Encrypted key: %s\n", encryptedKey);
    free(encryptedKey);
    return 0;
}