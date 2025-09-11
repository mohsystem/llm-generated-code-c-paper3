#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* id;
    RSA* key;
} KeyPair;

KeyPair* keys = NULL;
int keys_size = 0;

void generateKey(const char* id) {
    for (int i = 0; i < keys_size; i++) {
        if (strcmp(keys[i].id, id) == 0) {
            fprintf(stderr, "Key with ID %s already exists.\n", id);
            exit(1);
        }
    }
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, e, NULL);
    keys = realloc(keys, (keys_size + 1) * sizeof(KeyPair));
    keys[keys_size].id = strdup(id);
    keys[keys_size].key = rsa;
    keys_size++;
}

RSA* getKey(const char* id) {
    for (int i = 0; i < keys_size; i++) {
        if (strcmp(keys[i].id, id) == 0) {
            return keys[i].key;
        }
    }
    fprintf(stderr, "Key with ID %s does not exist.\n", id);
    exit(1);
}

void deleteKey(const char* id) {
    for (int i = 0; i < keys_size; i++) {
        if (strcmp(keys[i].id, id) == 0) {
            RSA_free(keys[i].key);
            free(keys[i].id);
            memmove(keys + i, keys + i + 1, (keys_size - i - 1) * sizeof(KeyPair));
            keys_size--;
            keys = realloc(keys, keys_size * sizeof(KeyPair));
            return;
        }
    }
    fprintf(stderr, "Key with ID %s does not exist.\n", id);
    exit(1);
}