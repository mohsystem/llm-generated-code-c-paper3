#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    RSA* rsa;
    char* keyName;
} KeyPair;

typedef struct {
    KeyPair** keyStore;
    int size;
} KeyManager;

KeyManager* keyManagerInit() {
    KeyManager* km = malloc(sizeof(KeyManager));
    km->keyStore = NULL;
    km->size = 0;
    return km;
}

void keyManagerAddKey(KeyManager* km, const char* keyName, RSA* rsa) {
    km->size++;
    km->keyStore = realloc(km->keyStore, km->size * sizeof(KeyPair*));
    KeyPair* kp = malloc(sizeof(KeyPair));
    kp->rsa = rsa;
    kp->keyName = strdup(keyName);
    km->keyStore[km->size - 1] = kp;
}

RSA* keyManagerGetKey(KeyManager* km, const char* keyName) {
    for (int i = 0; i < km->size; i++) {
        if (strcmp(km->keyStore[i]->keyName, keyName) == 0) {
            return km->keyStore[i]->rsa;
        }
    }
    return NULL;
}

void printRSA(RSA* rsa) {
    const BIGNUM* n = RSA_get0_key(rsa, NULL, NULL);
    const BIGNUM* e = RSA_get0_key(rsa, NULL, NULL);
    const BIGNUM* d = RSA_get0_key(rsa, NULL, NULL);

    char* n_str = BN_bn2hex(n);
    char* e_str = BN_bn2hex(e);
    char* d_str = BN_bn2hex(d);

    printf("N: %s\n", n_str);
    printf("E: %s\n", e_str);
    printf("D: %s\n", d_str);

    OPENSSL_free(n_str);
    OPENSSL_free(e_str);
    OPENSSL_free(d_str);
}

int main() {
    KeyManager* km = keyManagerInit();

    // Test cases
    const char* keyNames[] = {"key1", "key2", "key3", "key4", "key5"};

    for (int i = 0; i < 5; i++) {
        RSA* rsa = RSA_new();
        BIGNUM* exponent = BN_new();
        BN_set_word(exponent, 65537);
        RSA_generate_key_ex(rsa, 2048, exponent, NULL);
        BN_free(exponent);

        keyManagerAddKey(km, keyNames[i], rsa);

        RSA* retrievedKey = keyManagerGetKey(km, keyNames[i]);
        printf("Key Name: %s\n", keyNames[i]);
        printf("Public Key: \n");
        printRSA(retrievedKey);
        printf("Private Key: \n");
        printRSA(retrievedKey);
        printf("\n");
    }

    return 0;
}