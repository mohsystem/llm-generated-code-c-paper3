#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void printHash(const unsigned char* hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
}

int main() {
    const char* password = "farm1990M0O";
    const char* salt = "f1nd1ngn3m0";

    // Prepending the salt
    char saltedPassword[1024];
    snprintf(saltedPassword, sizeof(saltedPassword), "%s%s", salt, password);
    unsigned char hash1[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, saltedPassword, strlen(saltedPassword));
    SHA256_Final(hash1, &sha256);

    // Appending the salt
    snprintf(saltedPassword, sizeof(saltedPassword), "%s%s", password, salt);
    unsigned char hash2[SHA256_DIGEST_LENGTH];
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, saltedPassword, strlen(saltedPassword));
    SHA256_Final(hash2, &sha256);

    printf("Hash with prepended salt: ");
    printHash(hash1);
    printf("\n");

    printf("Hash with appended salt: ");
    printHash(hash2);
    printf("\n");

    return 0;
}