#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

char* encrypt(const char* text) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, text, strlen(text));
    SHA256_Final(hash, &sha256);

    BIO *bio = BIO_new(BIO_s_mem());
    BIO *b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, hash, SHA256_DIGEST_LENGTH);
    BIO_flush(bio);
    BUF_MEM *bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    char *result = (char*) malloc(bufferPtr->length + 1);
    strcpy(result, bufferPtr->data);
    BIO_free_all(bio);

    return result;
}

int main() {
    char* encrypted1 = encrypt("Hello");
    printf("%s\n", encrypted1);
    free(encrypted1);

    char* encrypted2 = encrypt("World");
    printf("%s\n", encrypted2);
    free(encrypted2);


    char* encrypted3 = encrypt("Test1");
    printf("%s\n", encrypted3);
    free(encrypted3);

    char* encrypted4 = encrypt("Test2");
    printf("%s\n", encrypted4);
    free(encrypted4);

    char* encrypted5 = encrypt("Test3");
    printf("%s\n", encrypted5);
    free(encrypted5);


    return 0;
}