#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

RSA* createRSAWithFilename(char* filename, int public) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Unable to open file %s \n", filename);
        return NULL;
    }
    RSA* rsa = RSA_new();
    if (public) {
        rsa = PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
    } else {
        rsa = PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
    }
    fclose(fp);
    return rsa;
}

int public_encrypt(unsigned char* data, int data_len, RSA* rsa, unsigned char* encrypted) {
    int result = RSA_public_encrypt(data_len, data, encrypted, rsa, RSA_PKCS1_OAEP_PADDING);
    return result;
}

int private_decrypt(unsigned char* enc_data, int data_len, RSA* rsa, unsigned char* decrypted) {
    int result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, RSA_PKCS1_OAEP_PADDING);
    return result;
}

void generate_keys() {
    int ret = 0;
    RSA* r = NULL;
    BIGNUM* bne = NULL;
    BIO *bp_public = NULL, *bp_private = NULL;

    int bits = 2048;
    unsigned long e = RSA_F4;

    bne = BN_new();
    ret = BN_set_word(bne, e);
    if (ret != 1) {
        handleErrors();
    }

    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);
    if (ret != 1) {
        handleErrors();
    }

    bp_public = BIO_new_file("public.pem", "w+");
    ret = PEM_write_bio_RSAPublicKey(bp_public, r);
    if (ret != 1) {
        handleErrors();
    }

    bp_private = BIO_new_file("private.pem", "w+");
    ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);
    if (ret != 1) {
        handleErrors();
    }

    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    RSA_free(r);
    BN_free(bne);
}

int main() {
    generate_keys();
    char plainText[2048/8] = "Hello World!";
    unsigned char encrypted[4098] = {};
    unsigned char decrypted[4098] = {};

    RSA* publicRSA = createRSAWithFilename("public.pem", 1);
    int encrypted_length = public_encrypt(plainText, strlen(plainText), publicRSA, encrypted);
    if (encrypted_length == -1) {
        handleErrors();
    }

    RSA* privateRSA = createRSAWithFilename("private.pem", 0);
    int decrypted_length = private_decrypt(encrypted, encrypted_length, privateRSA, decrypted);
    if (decrypted_length == -1) {
        handleErrors();
    }

    printf("Decrypted Text = %s\n", decrypted);

    return 0;
}