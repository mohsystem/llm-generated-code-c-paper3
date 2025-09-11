#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

char* generateAndExportRsaPrivateKey() {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, 65537);
    RSA_generate_key_ex(rsa, 2048, e, NULL);
    BN_free(e);

    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);


    char* pem_data;
    long pem_len = BIO_get_mem_data(bio, &pem_data);

    char *pem_key = (char *)malloc(pem_len + 1);
    if(pem_key == NULL) {
       perror("Failed to allocate memory");
       RSA_free(rsa);
       BIO_free_all(bio);
       return NULL; 
    }
    memcpy(pem_key, pem_data, pem_len);
    pem_key[pem_len] = '\0';

    BIO_free_all(bio);
    RSA_free(rsa);

    return pem_key;
}

int main() {
    char *key;

    printf("Test case 1:\n");
    key = generateAndExportRsaPrivateKey();
    if (key != NULL) {
      printf("%s\n", key);
      free(key);
    }

    printf("\nTest case 2:\n");
    key = generateAndExportRsaPrivateKey();
    if (key != NULL) {
      printf("%s\n", key);
      free(key);
    }

    printf("\nTest case 3:\n");
     key = generateAndExportRsaPrivateKey();
    if (key != NULL) {
      printf("%s\n", key);
      free(key);
    }

    printf("\nTest case 4:\n");
    key = generateAndExportRsaPrivateKey();
    if (key != NULL) {
      printf("%s\n", key);
      free(key);
    }

    printf("\nTest case 5:\n");
    key = generateAndExportRsaPrivateKey();
    if (key != NULL) {
      printf("%s\n", key);
      free(key);
    }


    return 0;
}