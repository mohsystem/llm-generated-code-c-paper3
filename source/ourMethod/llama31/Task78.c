#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>

int main() {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    BN_set_word(bne, RSA_F4);

    RSA_generate_key_ex(rsa, 2048, bne, NULL);

    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

    char *buffer;
    long len = BIO_get_mem_data(bio, &buffer);
    FILE *file = fopen("private_key.pem", "w");
    fwrite(buffer, 1, len, file);
    fclose(file);

    BIO_free(bio);
    BN_free(bne);
    RSA_free(rsa);

    return 0;
}