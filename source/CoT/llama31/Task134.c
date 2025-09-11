#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

typedef struct {
    RSA* rsa;
    char keyId[256];
} KeyStoreEntry;

typedef struct {
    KeyStoreEntry* entries;
    int size;
} KeyStore;

void generateKey(KeyStore* store, const char* keyId) {
    RSA* rsa = RSA_new();
    BIGNUM* exponent = BN_new();
    BN_set_word(exponent, 65537);
    RSA_generate_key_ex(rsa, 2048, exponent, NULL);

    KeyStoreEntry* newEntry = malloc(sizeof(KeyStoreEntry));
    newEntry->rsa = rsa;
    strcpy(newEntry->keyId, keyId);

    store->entries = realloc(store->entries, (store->size + 1) * sizeof(KeyStoreEntry));
    store->entries[store->size++] = *newEntry;
}

RSA* getKey(KeyStore* store, const char* keyId) {
    for (int i = 0; i < store->size; i++) {
        if (strcmp(store->entries[i].keyId, keyId) == 0) {
            return store->entries[i].rsa;
        }
    }
    return NULL;
}

int main() {
    KeyStore store;
    store.entries = NULL;
    store.size = 0;

    generateKey(&store, "key1");
    generateKey(&store, "key2");

    RSA* kp1 = getKey(&store, "key1");
    if (kp1) {
        printf("Public Key: %p\n", kp1);
        printf("Private Key: %p\n", kp1);
    }

    RSA* kp2 = getKey(&store, "key2");
    if (kp2) {
        printf("Public Key: %p\n", kp2);
        printf("Private Key: %p\n", kp2);
    }

    return 0;
}