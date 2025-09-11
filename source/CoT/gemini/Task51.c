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
    char *result = (char *)malloc(bufferPtr->length + 1);
    strcpy(result, bufferPtr->data);

    BIO_free_all(bio);

    return result;
}

int main() {
    char *encryptedText;

    encryptedText = encrypt("Test1");
    printf("%s\n", encryptedText);
    free(encryptedText);

    encryptedText = encrypt("Test2");
    printf("%s\n", encryptedText);
    free(encryptedText);

    encryptedText = encrypt("Test3");
    printf("%s\n", encryptedText);
    free(encryptedText);

    encryptedText = encrypt("Test4");
    printf("%s\n", encryptedText);
    free(encryptedText);

    encryptedText = encrypt("Test5");
    printf("%s\n", encryptedText);
    free(encryptedText);

    return 0;
}