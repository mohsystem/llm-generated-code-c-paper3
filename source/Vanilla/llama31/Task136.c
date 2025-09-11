#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';
}

int authenticate(const char* username, const char* password, const char* storedHash) {
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    hashPassword(password, hashedPassword);
    return strcmp(hashedPassword, storedHash) == 0;
}

int main() {
    const char* username = "testuser";
    const char* password = "testpassword";
    char storedHash[SHA256_DIGEST_LENGTH * 2 + 1];
    hashPassword(password, storedHash);

    // Test cases
    printf("Authentication result for correct credentials: %d\n", authenticate(username, password, storedHash));
    printf("Authentication result for incorrect password: %d\n", authenticate(username, "wrongpassword", storedHash));
    printf("Authentication result for incorrect username: %d\n", authenticate("wronguser", password, storedHash));
    printf("Authentication result for empty password: %d\n", authenticate(username, "", storedHash));
    printf("Authentication result for empty username: %d\n", authenticate("", password, storedHash));

    return 0;
}