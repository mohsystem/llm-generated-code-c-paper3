
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define BUFFER_SIZE 4096

char* generate_openssh_private_key() {
    static char buffer[BUFFER_SIZE];
    buffer[0] = '\0';
    
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    
    // Generate key
    RSA* rsa = RSA_new();
    BIGNUM* bne = BN_new();
    BN_set_word(bne, RSA_F4);
    
    if(RSA_generate_key_ex(rsa, 2048, bne, NULL) != 1) {
        ERR_print_errors_fp(stderr);
        strcpy(buffer, "Error generating RSA key");
        return buffer;
    }
    
    // Convert to OpenSSH format
    BIO* bio = BIO_new(BIO_s_mem());
    if(PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL) != 1) {
        ERR_print_errors_fp(stderr);
        strcpy(buffer, "Error writing key");
        return buffer;
    }
    
    // Read from BIO to buffer
    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    if(bptr->length >= BUFFER_SIZE) {
        strcpy(buffer, "Buffer too small");
        return buffer;
    }
    memcpy(buffer, bptr->data, bptr->length);
    buffer[bptr->length] = '\0';
    
    // Cleanup
    BIO_free(bio);
    RSA_free(rsa);
    BN_free(bne);
    
    return buffer;
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        printf("Test case %d:\\n", i+1);
        char* key = generate_openssh_private_key();
        printf("%s\\n\\n", key);
    }
    
    return 0;
}
