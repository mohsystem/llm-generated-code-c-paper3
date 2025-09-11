#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

// Simple hash function using SHA-256
void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
}

typedef struct {
    char username[100];
    char hashedPassword[65]; // 64 characters for hex + 1 for null terminator
} User;

User users[10]; // Simple array for demonstration
int userCount = 0;

void registerUser(const char* username, const char* password) {
    if (userCount < 10) {
        strcpy(users[userCount].username, username);
        hashPassword(password, users[userCount].hashedPassword);
        userCount++;
    } else {
        printf("User limit reached.\n");
    }
}

bool authenticateUser(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            char providedHash[65];
            hashPassword(password, providedHash);
            return strcmp(users[i].hashedPassword, providedHash) == 0;
        }
    }
    return false;
}

int main() {
    // Test cases
    registerUser("user1", "password123");
    registerUser("user2", "password456");

    printf("%d\n", authenticateUser("user1", "password123")); // 1 (true)
    printf("%d\n", authenticateUser("user1", "wrongpassword")); // 0 (false)
    printf("%d\n", authenticateUser("user2", "password456")); // 1 (true)

    return 0;
}