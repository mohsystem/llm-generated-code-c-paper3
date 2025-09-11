#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string.h>


char* encode_public_key(RSA* rsa) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bio, rsa);
    char *data;
    long len = BIO_get_mem_data(bio, &data);
    char* pem = malloc(len + 1); // Allocate memory for the string
    memcpy(pem, data, len);
    pem[len] = '\0'; // Null-terminate the string
    BIO_free_all(bio);
    return pem;
}

char* encode_private_key(RSA* rsa) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
    char *data;
    long len = BIO_get_mem_data(bio, &data);
    char* pem = malloc(len + 1); 
    memcpy(pem, data, len);
    pem[len] = '\0'; 
    BIO_free_all(bio);
    return pem;
}


RSA* generate_rsa_keypair() {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    BN_set_word(bne, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, bne, NULL);
    BN_free(bne);
    return rsa;
}


int main() {
    for (int i = 1; i <= 5; ++i) {
        RSA* rsa = generate_rsa_keypair();
        char* pub_key = encode_public_key(rsa);
        char* priv_key = encode_private_key(rsa);
        printf("Public Key %d: %s\n", i, pub_key);
        printf("Private Key %d: %s\n", i, priv_key);
        free(pub_key);  // Free allocated memory
        free(priv_key); // Free allocated memory
        RSA_free(rsa);
    }
    return 0;
}