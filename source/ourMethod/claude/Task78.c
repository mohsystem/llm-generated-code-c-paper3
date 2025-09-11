
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define KEY_SIZE 2048
#define BUFFER_SIZE 4096

struct Task78 {
    char* (*generateOpenSSHPrivateKey)();
};

char* generateOpenSSHPrivateKey() {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    
    // Generate RSA key pair
    RSA* rsa = RSA_new();
    BIGNUM* bne = BN_new();
    BN_set_word(bne, RSA_F4);
    
    if (RSA_generate_key_ex(rsa, KEY_SIZE, bne, NULL) != 1) {
        BN_free(bne);
        RSA_free(rsa);
        return NULL;
    }
    
    // Convert to OpenSSH format
    BIO* bio = BIO_new(BIO_s_mem());
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        BIO_free_all(bio);
        BN_free(bne);
        RSA_free(rsa);
        return NULL;
    }
    
    // Get key string
    char* key = malloc(BUFFER_SIZE);
    if (!key) {
        BIO_free_all(bio);
        BN_free(bne);
        RSA_free(rsa);
        return NULL;
    }
    
    int keyLen = BIO_read(bio, key, BUFFER_SIZE-1);
    if (keyLen > 0) {
        key[keyLen] = '\\0';
    } else {
        free(key);
        key = NULL;
    }
    
    // Cleanup
    BIO_free_all(bio);
    BN_free(bne);
    RSA_free(rsa);
    
    return key;
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        char* key = generateOpenSSHPrivateKey();
        if (key) {
            printf("Generated Key %d:\\n%s\\n\\n", i+1, key);
            free(key);
        } else {
            fprintf(stderr, "Error generating key\\n");
            return 1;
        }
    }
    return 0;
}
