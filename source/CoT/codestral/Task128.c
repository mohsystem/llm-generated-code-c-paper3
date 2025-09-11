#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

char *generate_random_token(int length) {
    unsigned char *random_bytes = malloc(length);
    RAND_bytes(random_bytes, length);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, random_bytes, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char *token = malloc(bufferPtr->length + 1);
    memcpy(token, bufferPtr->data, bufferPtr->length);
    token[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    free(random_bytes);

    return token;
}

int main() {
    printf("%s\n", generate_random_token(16));
    printf("%s\n", generate_random_token(16));
    printf("%s\n", generate_random_token(16));
    printf("%s\n", generate_random_token(16));
    printf("%s\n", generate_random_token(16));
    return 0;
}