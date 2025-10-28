#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This code requires OpenSSL 3.0+
// To compile: gcc your_file.c -o your_app -lssl -lcrypto
#include <openssl/evp.h>
#include <openssl/encoder.h>
#include <openssl/rsa.h>
#include <openssl/bio.h>

/**
 * Generates an RSA private key and exports it using the OpenSSH format.
 * The caller is responsible for freeing the returned string.
 *
 * @param keySize The size of the key in bits (e.g., 2048, 4096).
 * @return A dynamically allocated string containing the key, or NULL on failure.
 */#include <openssl/evp.h>
#include <openssl/encoder.h>
#include <openssl/bio.h>

char* generateOpenSSHPrivateKey(int keySize) {
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        fprintf(stderr, "Failed to create EVP_PKEY_CTX\n");
        return NULL;
    }

    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        fprintf(stderr, "Failed to initialize keygen context\n");
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }

    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, keySize) <= 0) {
        fprintf(stderr, "Failed to set RSA key bits\n");
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }

    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        fprintf(stderr, "Failed to generate key\n");
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }

    EVP_PKEY_CTX_free(ctx);

    BIO *bio = BIO_new(BIO_s_mem());
    if (!bio) {
        fprintf(stderr, "Failed to create BIO\n");
        EVP_PKEY_free(pkey);
        return NULL;
    }

    OSSL_ENCODER_CTX *ectx = OSSL_ENCODER_CTX_new_for_pkey(
        pkey,
        /* selection */ EVP_PKEY_PRIVATE_KEY,   // If you target OpenSSL 3.x, consider OSSL_KEYMGMT_SELECT_PRIVATE_KEY
        /* output type */ "PEM",
        /* output structure */ "openssh",
        /* propq */ NULL
    );
    if (!ectx) {
        fprintf(stderr, "Failed to create OSSL_ENCODER_CTX\n");
        BIO_free(bio);
        EVP_PKEY_free(pkey);
        return NULL;
    }

    if (OSSL_ENCODER_to_bio(ectx, bio) <= 0) {
        fprintf(stderr, "Failed to encode key to BIO\n");
        OSSL_ENCODER_CTX_free(ectx);
        BIO_free(bio);
        EVP_PKEY_free(pkey);
        return NULL;
    }

    // Read the memory BIO without touching BUF_MEM internals
    char *data = NULL;
    long len = BIO_get_mem_data(bio, &data);
    if (len <= 0 || data == NULL) {
        fprintf(stderr, "Failed to get data from BIO\n");
        OSSL_ENCODER_CTX_free(ectx);
        BIO_free_all(bio);
        EVP_PKEY_free(pkey);
        return NULL;
    }

    char *key_str = (char*)malloc((size_t)len + 1);
    if (!key_str) {
        fprintf(stderr, "Failed to allocate memory for key string\n");
        OSSL_ENCODER_CTX_free(ectx);
        BIO_free_all(bio);
        EVP_PKEY_free(pkey);
        return NULL;
    }
    memcpy(key_str, data, (size_t)len);
    key_str[len] = '\0';

    // Cleanup
    OSSL_ENCODER_CTX_free(ectx);
    BIO_free_all(bio);
    EVP_PKEY_free(pkey);

    return key_str;
}

int main() {
    int testKeySizes[] = {1024, 1024, 2048, 2048, 4096};
    for (int i = 0; i < 5; ++i) {
        printf("--- Test Case %d: Generating %d-bit key ---\n", (i + 1), testKeySizes[i]);
        if (testKeySizes[i] < 2048) {
            printf("(Note: %d-bit RSA is considered weak for production use.)\n", testKeySizes[i]);
        }
        char *key = generateOpenSSHPrivateKey(testKeySizes[i]);
        if (key) {
            printf("%s\n", key);
            free(key); // Free the memory allocated by the function
        } else {
            printf("Key generation failed.\n\n");
        }
    }
    return 0;
}