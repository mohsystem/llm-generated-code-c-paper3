#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

char* generateRSAPrivateKey() {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    char *privateKeyPem = NULL;

    if (!BN_set_word(bne, RSA_F4)) {
        RSA_free(rsa);
        BN_free(bne);
        return NULL;
    }

    if (!RSA_generate_key_ex(rsa, 2048, bne, NULL)) {
        RSA_free(rsa);
        BN_free(bne);
        return NULL;
    }

    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
    
    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    privateKeyPem = (char*)malloc(bptr->length + 1);
    memcpy(privateKeyPem, bptr->data, bptr->length);
    privateKeyPem[bptr->length] = '\0';

    BIO_free_all(bio);
    RSA_free(rsa);
    BN_free(bne);

    return privateKeyPem;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        printf("Test case %d:\n", i + 1);
        char* privateKey = generateRSAPrivateKey();
        if (privateKey != NULL) {
            printf("%s\n", privateKey);
            free(privateKey);
        }
    }
    return 0;
}