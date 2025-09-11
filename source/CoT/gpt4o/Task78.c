#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>

char* generateRSAPrivateKey() {
    int ret = 0;
    RSA *r = NULL;
    BIGNUM *bne = NULL;
    BIO *bp_private = NULL;
    char *private_key = NULL;

    int bits = 2048;
    unsigned long e = RSA_F4;

    bne = BN_new();
    ret = BN_set_word(bne, e);
    if (ret != 1) {
        goto free_all;
    }

    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);
    if (ret != 1) {
        goto free_all;
    }

    bp_private = BIO_new(BIO_s_mem());
    ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);
    if (ret != 1) {
        goto free_all;
    }

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bp_private, &bptr);
    private_key = malloc(bptr->length + 1);
    memcpy(private_key, bptr->data, bptr->length);
    private_key[bptr->length] = '\0';

free_all:
    BIO_free_all(bp_private);
    RSA_free(r);
    BN_free(bne);

    return private_key;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* privateKey = generateRSAPrivateKey();
        if (privateKey) {
            printf("%s\n", privateKey);
            free(privateKey);
        }
    }
    return 0;
}