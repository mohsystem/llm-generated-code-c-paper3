//  OpenSSL library is required to compile and run this code.
//  gcc task78.c -lcrypto -o task78 && ./task78


#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string.h>


char* generate_and_export_rsa_private_key() {
    RSA* rsa = RSA_new();
    BIGNUM* bne = BN_new();
    int rc = BN_set_word(bne, RSA_F4); // Public exponent 65537

    if(rc != 1 || !rsa || !bne){
        // Handle error
        if (rsa) RSA_free(rsa);
        if (bne) BN_free(bne);
        return NULL;
    }
    
    rc = RSA_generate_key_ex(rsa, 2048, bne, NULL);
    if(rc != 1){
         // Handle error
        if (rsa) RSA_free(rsa);
        if (bne) BN_free(bne);
        return NULL;       
    }
    BN_free(bne);


    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        RSA_free(rsa);
        return NULL;
    }

    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
    
    char* pem_data;
    long len = BIO_get_mem_data(bio, &pem_data);

    char *pem_string = (char *)malloc((len + 1) * sizeof(char));
    if (pem_string == NULL) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return NULL;
    }
    strncpy(pem_string, pem_data, len);
    pem_string[len] = '\0';


    BIO_free_all(bio);
    RSA_free(rsa);


    char *openssh_key = (char *)malloc( (strlen(pem_string) + 100) * sizeof(char));  // Allocate sufficient memory
    if(openssh_key == NULL){
        free(pem_string);
        return NULL;
    }
    strcpy(openssh_key, "-----BEGIN OPENSSH PRIVATE KEY-----\n");
    
    char *current_pos = openssh_key + strlen(openssh_key);
    for (int i = 0; i < strlen(pem_string); i++) {
        if (pem_string[i] != '\n' && pem_string[i] != '\r' && pem_string[i] != '-') {
            *current_pos++ = pem_string[i];

        }
    }

    strcat(openssh_key, "\n-----END OPENSSH PRIVATE KEY-----\n");
    free(pem_string);

    return openssh_key;
}


int main() {
    for (int i = 0; i < 5; i++) {
        char *private_key = generate_and_export_rsa_private_key();
        if(private_key != NULL) {
            printf("%s\n", private_key);
            printf("--------------------\n");
            free(private_key); // Free the allocated memory
        } else {
            fprintf(stderr, "Error generating key.\n");
        }

    }
    return 0;
}