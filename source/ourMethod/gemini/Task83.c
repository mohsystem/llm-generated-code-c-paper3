#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>


char* base64_encode(const unsigned char* input, int length) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *result = (char *)malloc(bptr->length + 1);
    memcpy(result, bptr->data, bptr->length);
    result[bptr->length] = '\0';
    BIO_free_all(b64);
    return result;
}



char *encrypt(const char *key) {
    char *key_to_use;

     if (key == NULL || strlen(key) == 0) {
        unsigned char key_bytes[17];  // 16 bytes for the key + 1 for null terminator
        RAND_bytes(key_bytes, 16);
        key_bytes[16] = '\0';  // Null-terminate
        key_to_use = base64_encode(key_bytes, 16);

    } else {
        key_to_use = strdup(key);
    }


    unsigned char key_bytes[strlen(key_to_use)];
    memcpy(key_bytes, key_to_use, strlen(key_to_use));


    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);


    AES_KEY aes_key;
    if (AES_set_encrypt_key(key_bytes, 128, &aes_key) < 0) {
         free(key_to_use);
        return NULL;
    }

    // Calculate the size of the encrypted key, including padding.
    int padded_len = strlen(key_to_use) + AES_BLOCK_SIZE - (strlen(key_to_use) % AES_BLOCK_SIZE);
    unsigned char encrypted_key[padded_len];

    AES_cbc_encrypt((unsigned char *)key_to_use, encrypted_key, strlen(key_to_use), &aes_key, iv, AES_ENCRYPT);


    unsigned char combined[AES_BLOCK_SIZE + padded_len];
    memcpy(combined, iv, AES_BLOCK_SIZE);
    memcpy(combined + AES_BLOCK_SIZE, encrypted_key, padded_len);

    char *base64_combined = base64_encode(combined, sizeof(combined));
    free(key_to_use);
    return base64_combined;
}

int main() {
    char *testCases[] = {"test1", "test2test2", "", "longerkeytest", NULL};
    int i = 0;
    while (testCases[i] != NULL) {
        char *encrypted = encrypt(testCases[i]);
        if (encrypted != NULL) {
            printf("Encrypted: %s\n", encrypted);
            free(encrypted);
        }
        i++;
    }
      char *encrypted = encrypt(testCases[4]);
        if (encrypted != NULL) {
            printf("Encrypted: %s\n", encrypted);
            free(encrypted);
        }

    return 0;
}