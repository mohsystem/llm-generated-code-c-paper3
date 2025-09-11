#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

char *hash_password(const char *password, const char *salt) {
    char *combined = malloc(strlen(password) + strlen(salt) + 1);
    strcpy(combined, password);
    strcat(combined, salt);

    const EVP_MD *md = EVP_get_digestbyname("sha256");
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, combined, strlen(combined));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, md_value, md_len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char *hash = malloc(bufferPtr->length + 1);
    memcpy(hash, bufferPtr->data, bufferPtr->length);
    hash[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    free(combined);

    return hash;
}

int main() {
    printf("%s\n", hash_password("password1", "salt1"));
    printf("%s\n", hash_password("password2", "salt2"));
    printf("%s\n", hash_password("password3", "salt3"));
    printf("%s\n", hash_password("password4", "salt4"));
    printf("%s\n", hash_password("password5", "salt5"));

    return 0;
}