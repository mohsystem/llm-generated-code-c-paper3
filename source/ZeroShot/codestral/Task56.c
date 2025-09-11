#include <stdio.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

char* generate_token() {
    unsigned char token[24];
    RAND_bytes(token, sizeof(token));

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, token, sizeof(token));
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char* result = malloc(bufferPtr->length + 1);
    memcpy(result, bufferPtr->data, bufferPtr->length);
    result[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    return result;
}

int main() {
    printf("%s\n", generate_token());
    printf("%s\n", generate_token());
    printf("%s\n", generate_token());
    printf("%s\n", generate_token());
    printf("%s\n", generate_token());

    return 0;
}