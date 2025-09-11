#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <base64.h>

char* hashPassword(const char* password) {
    unsigned char salt[16];
    RAND_bytes(salt, 16);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, 16);
    SHA256_Final(hash, &sha256);

    // Combine salt and hashed password
    char combined[16 + SHA256_DIGEST_LENGTH];
    memcpy(combined, salt, 16);
    memcpy(combined + 16, hash, SHA256_DIGEST_LENGTH);

    // Base64 encode the combined bytes
    char* encoded = base64_encode(combined, 16 + SHA256_DIGEST_LENGTH);

    return encoded;
}

int main() {
    const char* password = "MySecretPassword";
    char* hashedPassword = hashPassword(password);
    printf("Hashed password: %s\n", hashedPassword);

    free(hashedPassword); // Don't forget to free the memory

    return 0;
}