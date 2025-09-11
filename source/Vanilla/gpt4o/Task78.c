#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

char* generatePrivateKey() {
    int bits = 2048;
    unsigned long e = RSA_F4;
    RSA* rsa = RSA_generate_key(bits, e, NULL, NULL);

    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

    char* privKey;
    long privKeyLen = BIO_get_mem_data(bio, &privKey);
    char* privKeyCopy = malloc(privKeyLen + 1);
    memcpy(privKeyCopy, privKey, privKeyLen);
    privKeyCopy[privKeyLen] = '\0';

    BIO_free(bio);
    RSA_free(rsa);

    return privKeyCopy;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* privateKey = generatePrivateKey();
        printf("%s\n", privateKey);
        free(privateKey);
    }
    return 0;
}