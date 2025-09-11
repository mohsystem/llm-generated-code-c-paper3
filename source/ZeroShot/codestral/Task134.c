// C does not have built-in support for maps, so this example uses a simple array to store keys.
// Also, C does not have built-in support for secure random number generation, so this example uses a less secure method.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#define MAX_KEYS 100
#define MAX_KEY_LENGTH 30

char keys[MAX_KEYS][MAX_KEY_LENGTH];

char* generateKey() {
    unsigned char buffer[20];
    for(int i = 0; i < 20; i++) {
        buffer[i] = rand() % 256;
    }
    BIO* bio = BIO_new(BIO_s_mem());
    BIO_write(bio, buffer, 20);
    BUF_MEM* bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char* base64_buffer = malloc(EVP_EncodeBlock(bptr->length) + 1);
    EVP_EncodeBlock((unsigned char*)base64_buffer, bptr->data, bptr->length);
    BIO_free(bio);
    return base64_buffer;
}

void saveKey(int id, char* key) {
    if(id < MAX_KEYS) {
        strncpy(keys[id], key, MAX_KEY_LENGTH);
    }
}

char* getKey(int id) {
    if(id < MAX_KEYS) {
        return keys[id];
    }
    return NULL;
}

int main() {
    char* key1 = generateKey();
    saveKey(0, key1);
    printf("%s", getKey(0));
    free(key1);
    return 0;
}