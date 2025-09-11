#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

char* encrypt(const char* data) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    BIO_push(b64, bio);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, data, strlen(data));
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bufferPtr);
    char* result = (char*)malloc(bufferPtr->length + 1);
    memcpy(result, bufferPtr->data, bufferPtr->length);
    result[bufferPtr->length] = '\0';
    BIO_free_all(b64);
    return result;
}

char* decrypt(const char* data) {
    BIO *bio, *b64;
    char inbuf[512];
    char* result = (char*)malloc(strlen(data));
    int resultLen = 0;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(data, strlen(data));
    BIO_push(b64, bio);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    int inlen;
    while ((inlen = BIO_read(b64, inbuf, 512)) > 0) {
        memcpy(result + resultLen, inbuf, inlen);
        resultLen += inlen;
    }
    result[resultLen] = '\0';
    BIO_free_all(b64);
    return result;
}

int main() {
    const char* testCases[] = {
        "1234-5678-9012-3456",
        "9876-5432-1098-7654",
        "1111-2222-3333-4444",
        "5555-6666-7777-8888",
        "9999-0000-1111-2222"
    };

    for (int i = 0; i < 5; ++i) {
        char* encrypted = encrypt(testCases[i]);
        char* decrypted = decrypt(encrypted);
        printf("Original: %s\n", testCases[i]);
        printf("Encrypted: %s\n", encrypted);
        printf("Decrypted: %s\n", decrypted);
        printf("\n");
        free(encrypted);
        free(decrypted);
    }

    return 0;
}