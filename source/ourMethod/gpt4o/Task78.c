#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

char* generateRSAPrivateKey() {
    int key_length = 2048;
    unsigned long exp = RSA_F4;

    RSA* rsa = RSA_generate_key(key_length, exp, NULL, NULL);
    BIO* bio = BIO_new(BIO_s_mem());
    
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
    RSA_free(rsa);

    char* pem_key = NULL;
    long pem_len = BIO_get_mem_data(bio, &pem_key);
    char* result = (char*)malloc(pem_len + 1);
    if (result) {
        memcpy(result, pem_key, pem_len);
        result[pem_len] = '\0';
    }
    
    BIO_free(bio);
    return result;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* key = generateRSAPrivateKey();
        printf("%s\n", key);
        free(key);
    }
    return 0;
}