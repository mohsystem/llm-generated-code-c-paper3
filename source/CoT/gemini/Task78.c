#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

char* generateAndExportRsaPrivateKey(int keySize) {
    // 1. Problem understanding: Generate RSA key, export in OpenSSH format.
    // 2. Security requirements: Secure key generation, error handling.

    if (keySize < 2048) {
        fprintf(stderr, "Key size must be at least 2048 bits.\n");
        return NULL;
    }


    // 3. Secure coding generation: Use OpenSSL for key operations.
    RSA* rsa = RSA_new();
    BIGNUM* bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA_generate_key_ex(rsa, keySize, bn, NULL);
    BN_free(bn);

    BIO* bio = BIO_new(BIO_s_mem());
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        RSA_free(rsa);
        BIO_free(bio);
        ERR_print_errors_fp(stderr); // Print OpenSSL errors
        return NULL;
    }

    // 4. Code review: Check for NULL, proper resource release.
    // 5. Secure code output: Return formatted key, clear errors.

    char* keyData;
    long keyLen = BIO_get_mem_data(bio, &keyData);
    char *privateKey = (char *)malloc(keyLen + 1); // Allocate memory for the key
    if (privateKey == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        RSA_free(rsa);
        BIO_free(bio);
        return NULL;
    }
    memcpy(privateKey, keyData, keyLen); // Copy the key data
    privateKey[keyLen] = '\0'; // Null-terminate


    RSA_free(rsa);
    BIO_free(bio);
    ERR_clear_error();

    return privateKey;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        char *privateKey = generateAndExportRsaPrivateKey(2048);
        if (privateKey != NULL) {
            printf("%s\n", privateKey);
            free(privateKey); // Free the allocated memory
        } else {
            fprintf(stderr, "Failed to generate private key.\n");
            return 1;
        }
    }

    return 0;
}