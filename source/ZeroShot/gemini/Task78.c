#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

char* generate_and_export_rsa_private_key(const char* passphrase) {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, 65537);
    RSA_generate_key_ex(rsa, 2048, e, NULL);
    BN_free(e);

    BIO* bio = BIO_new(BIO_s_mem());

     if (passphrase == NULL || strlen(passphrase) == 0) {
        PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
    } else {
        PEM_write_bio_RSAPrivateKey(bio, rsa, EVP_des_ede3_cbc(), (unsigned char*)passphrase, strlen(passphrase), NULL, NULL);
    }


    char* buffer;
    long len = BIO_get_mem_data(bio, &buffer);
    char *key = (char*)malloc(len + 1);
    memcpy(key, buffer, len);
    key[len] = '\0';

    BIO_free_all(bio);
    RSA_free(rsa);
    return key;

}

int main() {
    char *key1 = generate_and_export_rsa_private_key(NULL);
    printf("%s\n", key1);
    free(key1);

    char *key2 = generate_and_export_rsa_private_key("testpassword");
    printf("%s\n", key2);
    free(key2);

    char *key3 = generate_and_export_rsa_private_key("");
    printf("%s\n", key3);
    free(key3);

    char *key4 = generate_and_export_rsa_private_key("another_password");
    printf("%s\n", key4);
    free(key4);

    char *key5 = generate_and_export_rsa_private_key(NULL);
    printf("%s\n", key5);
    free(key5);


    return 0;
}