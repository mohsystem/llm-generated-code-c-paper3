#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


char* encrypt(const char *key) {
    unsigned char key_aes[16];
    unsigned char iv[16];
    RAND_bytes(key_aes, 16);
    RAND_bytes(iv, 16);

    unsigned char ciphertext[128]; 
    int ciphertext_len;

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Error: EVP_CIPHER_CTX_new failed\n");
        return NULL;
    }


    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key_aes, iv)) {
         fprintf(stderr, "Error: EVP_EncryptInit_ex failed\n");
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }


    int len;
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)key, strlen(key))) {
        fprintf(stderr, "Error: EVP_EncryptUpdate failed\n");
         EVP_CIPHER_CTX_free(ctx);
        return NULL;

    }
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        fprintf(stderr, "Error: EVP_EncryptFinal_ex failed\n");
         EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }
    ciphertext_len += len;
     EVP_CIPHER_CTX_free(ctx);

    unsigned char combined[16 + ciphertext_len];
    memcpy(combined, iv, 16);
    memcpy(combined + 16, ciphertext, ciphertext_len);

    
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, combined, 16 + ciphertext_len);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *encoded = (char*) malloc(bptr->length +1);
    if (encoded == NULL) return NULL; 
    memcpy(encoded, bptr->data, bptr->length);
    encoded[bptr->length] = '\0';
    BIO_free_all(bio);
    
    return encoded;
}

int main() {
    char *encrypted;

    encrypted = encrypt("testkey1");
    if(encrypted) { printf("%s\n", encrypted); free(encrypted); }

    encrypted = encrypt("testkey22");
    if(encrypted) { printf("%s\n", encrypted); free(encrypted); }
    
    encrypted = encrypt("testkey333");
     if(encrypted) { printf("%s\n", encrypted); free(encrypted); }

    encrypted = encrypt("testkey4444");
     if(encrypted) { printf("%s\n", encrypted); free(encrypted); }

    encrypted = encrypt("testkey55555");
     if(encrypted) { printf("%s\n", encrypted); free(encrypted); }

    return 0;
}