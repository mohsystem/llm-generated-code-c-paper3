#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* hash_password(const char* password, const unsigned char* salt) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, 16);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, hash, SHA256_DIGEST_LENGTH);
    BIO_flush(b64);
    BUF_MEM* bptr;
    BIO_get_mem_ptr(b64, &bptr);

    char* encoded = malloc(bptr->length + 1);
    memcpy(encoded, bptr->data, bptr->length);
    encoded[bptr->length] = '\0';

    BIO_free_all(b64);

    return encoded;
}

int main() {
    unsigned char salt[16];
    RAND_bytes(salt, 16);

    const char* password = "myPassword";
    char* hashed_password = hash_password(password, salt);
    printf("Hashed Password: %s\n", hashed_password);

    free(hashed_password);

    return 0;
}