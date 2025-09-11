#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/enc.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

void generateAuthenticationToken(const char* username, char* token) {
    // Problem understanding: Generate a unique token for user authentication
    // Security requirements: Use secure random number generation to prevent predictability

    // Secure coding generation: Use OpenSSL for secure random number generation and Base64 encoding
    unsigned char bytes[32];
    RAND_bytes(bytes, 32);

    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, bytes, 32);
    BIO_flush(bio);

    BUF_MEM* bptr;
    BIO_get_mem_ptr(bio, &bptr);
    memcpy(token, bptr->data, bptr->length);
    token[bptr->length] = '\0';

    BIO_free_all(bio);
}

int main() {
    // Test cases
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    char token[64];
    for (int i = 0; i < 5; ++i) {
        generateAuthenticationToken(usernames[i], token);
        printf("Token for %s: %s\n", usernames[i], token);
    }
    return 0;
}