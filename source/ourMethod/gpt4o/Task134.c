#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    char alias[50];
    EVP_PKEY* key;
} KeyStoreEntry;

typedef struct {
    KeyStoreEntry entries[10];
    int count;
} KeyStore;

void storeKey(KeyStore* keyStore, const char* alias, EVP_PKEY* key) {
    strcpy(keyStore->entries[keyStore->count].alias, alias);
    keyStore->entries[keyStore->count].key = key;
    keyStore->count++;
}

EVP_PKEY* retrieveKey(KeyStore* keyStore, const char* alias) {
    for (int i = 0; i < keyStore->count; i++) {
        if (strcmp(keyStore->entries[i].alias, alias) == 0) {
            return keyStore->entries[i].key;
        }
    }
    return NULL;
}

RSA* generateRSAKeyPair() {
    RSA* rsa = RSA_new();
    BIGNUM* bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, bn, NULL);
    BN_free(bn);
    return rsa;
}

EVP_PKEY* generateAESKey() {
    unsigned char key[32];
    RAND_bytes(key, sizeof(key));
    EVP_PKEY* pkey = EVP_PKEY_new_raw_private_key(EVP_PKEY_AES, NULL, key, sizeof(key));
    return pkey;
}

int main() {
    OpenSSL_add_all_algorithms();

    KeyStore keyStore = { .count = 0 };
    
    RSA* rsaKeyPair1 = generateRSAKeyPair();
    EVP_PKEY* rsaPublicKey1 = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(rsaPublicKey1, RSAPublicKey_dup(rsaKeyPair1));
    storeKey(&keyStore, "rsaPublicKey1", rsaPublicKey1);
    
    RSA* rsaKeyPair2 = generateRSAKeyPair();
    EVP_PKEY* rsaPublicKey2 = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(rsaPublicKey2, RSAPublicKey_dup(rsaKeyPair2));
    storeKey(&keyStore, "rsaPublicKey2", rsaPublicKey2);
    
    EVP_PKEY* aesKey1 = generateAESKey();
    storeKey(&keyStore, "aesKey1", aesKey1);
    
    EVP_PKEY* aesKey2 = generateAESKey();
    storeKey(&keyStore, "aesKey2", aesKey2);

    EVP_PKEY* aesKey3 = generateAESKey();
    storeKey(&keyStore, "aesKey3", aesKey3);
    
    // Test retrieval of keys
    printf("Retrieved RSA Public Key: %p\n", retrieveKey(&keyStore, "rsaPublicKey1"));
    printf("Retrieved AES Key: %p\n", retrieveKey(&keyStore, "aesKey1"));

    // Clean up
    RSA_free(rsaKeyPair1);
    RSA_free(rsaKeyPair2);
    EVP_PKEY_free(rsaPublicKey1);
    EVP_PKEY_free(rsaPublicKey2);
    EVP_PKEY_free(aesKey1);
    EVP_PKEY_free(aesKey2);
    EVP_PKEY_free(aesKey3);

    EVP_cleanup();

    return 0;
}