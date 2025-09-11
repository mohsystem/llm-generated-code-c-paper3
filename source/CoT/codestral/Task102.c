#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>
// For the database operations, you might need to include a library like libpq or sqlite3 and use it here

void updatePassword(const char* username, const char* password) {
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    getSecurePassword(password, hashedPassword);
    // Database update code here, using prepared statements to prevent SQL injection
}

void getSecurePassword(const char* passwordToHash, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, passwordToHash, strlen(passwordToHash));
    SHA256_Final(hash, &sha256);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = 0;
}

int main() {
    // Test cases
    updatePassword("user1", "password1");
    updatePassword("user2", "password2");
    updatePassword("user3", "password3");
    updatePassword("user4", "password4");
    updatePassword("user5", "password5");
    return 0;
}