#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

RSA* generateKey(int keySize) {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);
    RSA_generate_key_ex(rsa, keySize, e, NULL);
    BN_free(e);
    return rsa;
}

int main() {
    RSA* key1 = generateKey(2048);
    RSA* key2 = generateKey(2048);
    RSA* key3 = generateKey(2048);
    RSA* key4 = generateKey(2048);
    RSA* key5 = generateKey(2048);
    printf("Keys generated successfully.\n");
    RSA_free(key1);
    RSA_free(key2);
    RSA_free(key3);
    RSA_free(key4);
    RSA_free(key5);
    return 0;
}