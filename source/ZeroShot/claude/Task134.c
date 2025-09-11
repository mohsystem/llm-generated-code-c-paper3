
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define SYMMETRIC_KEY_LENGTH 32

typedef struct {
    unsigned char* symmetricKey;
    RSA* rsaKeyPair;
} KeyManager;

void initKeyManager(KeyManager* km) {
    km->symmetricKey = NULL;
    km->rsaKeyPair = NULL;
    OpenSSL_add_all_algorithms();
}

void cleanupKeyManager(KeyManager* km) {
    if (km->symmetricKey) free(km->symmetricKey);
    if (km->rsaKeyPair) RSA_free(km->rsaKeyPair);
    EVP_cleanup();
}

int generateSymmetricKey(KeyManager* km) {
    if (km->symmetricKey) free(km->symmetricKey);
    km->symmetricKey = (unsigned char*)malloc(SYMMETRIC_KEY_LENGTH);
    return RAND_bytes(km->symmetricKey, SYMMETRIC_KEY_LENGTH) == 1;
}

int generateAsymmetricKeys(KeyManager* km) {
    if (km->rsaKeyPair) RSA_free(km->rsaKeyPair);
    BIGNUM* bne = BN_new();
    BN_set_word(bne, RSA_F4);
    km->rsaKeyPair = RSA_new();
    int success = RSA_generate_key_ex(km->rsaKeyPair, 2048, bne, NULL) == 1;
    BN_free(bne);
    return success;
}

char* getEncodedSymmetricKey(KeyManager* km) {
    if (!km->symmetricKey) return NULL;
    char* encoded = (char*)malloc(SYMMETRIC_KEY_LENGTH * 2 + 1);
    for(int i = 0; i < SYMMETRIC_KEY_LENGTH; i++) {
        sprintf(&encoded[i*2], "%02x", km->symmetricKey[i]);
    }
    return encoded;
}

char* getEncodedPublicKey(KeyManager* km) {
    if (!km->rsaKeyPair) return NULL;
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bio, km->rsaKeyPair);
    char* pem = NULL;
    long length = BIO_get_mem_data(bio, &pem);
    char* result = (char*)malloc(length + 1);
    memcpy(result, pem, length);
    result[length] = '\\0';
    BIO_free(bio);
    return result;
}

char* getEncodedPrivateKey(KeyManager* km) {
    if (!km->rsaKeyPair) return NULL;
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, km->rsaKeyPair, NULL, NULL, 0, NULL, NULL);
    char* pem = NULL;
    long length = BIO_get_mem_data(bio, &pem);
    char* result = (char*)malloc(length + 1);
    memcpy(result, pem, length);
    result[length] = '\\0';
    BIO_free(bio);
    return result;
}

int main() {
    KeyManager km;
    initKeyManager(&km);
    
    // Test Case 1: Generate and retrieve symmetric key
    generateSymmetricKey(&km);
    char* symKey = getEncodedSymmetricKey(&km);
    printf("Test 1 - Symmetric Key: %s\\n", symKey);
    free(symKey);
    
    // Test Case 2: Generate and retrieve asymmetric keys
    generateAsymmetricKeys(&km);
    char* pubKey = getEncodedPublicKey(&km);
    printf("Test 2 - Public Key: %s\\n", pubKey);
    free(pubKey);
    
    // Test Case 3: Retrieve private key
    char* privKey = getEncodedPrivateKey(&km);
    printf("Test 3 - Private Key: %s\\n", privKey);
    free(privKey);
    
    // Test Case 4: Generate new symmetric key
    generateSymmetricKey(&km);
    symKey = getEncodedSymmetricKey(&km);
    printf("Test 4 - New Symmetric Key: %s\\n", symKey);
    free(symKey);
    
    // Test Case 5: Generate new asymmetric keys
    generateAsymmetricKeys(&km);
    pubKey = getEncodedPublicKey(&km);
    printf("Test 5 - New Public Key: %s\\n", pubKey);
    free(pubKey);
    
    cleanupKeyManager(&km);
    return 0;
}
