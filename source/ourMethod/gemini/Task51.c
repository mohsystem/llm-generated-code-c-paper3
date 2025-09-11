#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


char* encrypt(const char* text) {
    // Generate a secure random salt
    unsigned char salt[16];
    if (RAND_bytes(salt, sizeof(salt)) != 1) {
        fprintf(stderr, "Failed to generate salt\n");
        return NULL;
    }

    // Use SHA-256 for hashing
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, sizeof(salt));
    SHA256_Update(&sha256, text, strlen(text));
    SHA256_Final(hash, &sha256);

    // Combine salt and hash
    unsigned char saltAndHash[sizeof(salt) + SHA256_DIGEST_LENGTH];
    memcpy(saltAndHash, salt, sizeof(salt));
    memcpy(saltAndHash + sizeof(salt), hash, SHA256_DIGEST_LENGTH);

    // Base64 encode
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); 
    BIO_write(bio, saltAndHash, sizeof(saltAndHash));
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);

    char *encoded = (char*) malloc(bufferPtr->length +1); //+1 for null terminator
    if (encoded == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        BIO_free_all(bio);
        return NULL;
    }
    memcpy(encoded, bufferPtr->data, bufferPtr->length);
    encoded[bufferPtr->length] = '\0'; // Null-terminate the string


    BIO_free_all(bio);
    return encoded;
}

int main() {
    char* testCases[] = {"Hello", "World", "Test1", "Test2", "Test3"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char* encrypted = encrypt(testCases[i]);
        if (encrypted != NULL) {
            printf("Original: %s, Encrypted: %s\n", testCases[i], encrypted);
            free(encrypted); //Free allocated memory
        }
    }

    return 0;
}