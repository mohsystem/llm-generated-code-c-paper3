#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

typedef struct {
    RSA* rsa;
    char* keyId;
} KeyPair;

void generateKeyPair(KeyPair* keyPair) {
    keyPair->rsa = RSA_new();
    BIGNUM* bne = BN_new();
    BN_set_word(bne, RSA_F4);
    RSA_generate_key_ex(keyPair->rsa, 2048, bne, NULL);
    BN_free(bne);
}

void deleteKeyPair(KeyPair* keyPair) {
    RSA_free(keyPair->rsa);
    free(keyPair->keyId);
}

int main() {
    KeyPair keyPair;
    keyPair.keyId = "myKey";
    generateKeyPair(&keyPair);

    // Use the key pair
    RSA* publicKey = keyPair.rsa;
    RSA* privateKey = keyPair.rsa;

    // Delete the key pair
    deleteKeyPair(&keyPair);

    return 0;
}