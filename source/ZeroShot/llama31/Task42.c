#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char username[256];
    char hashedPassword[65];
} User;

User users[10];
int userCount = 0;

void registerUser(const char* username, const char* password) {
    if (userCount < 10) {
        strcpy(users[userCount].username, username);
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, password, strlen(password));
        SHA256_Final(hash, &sha256);
        for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            sprintf(users[userCount].hashedPassword + (i * 2), "%02x", hash[i]);
        }
        users[userCount].hashedPassword[64] = '\0';
        userCount++;
    }
}

int loginUser(const char* username, const char* password) {
    for(int i = 0; i < userCount; ++i) {
        if(strcmp(users[i].username, username) == 0) {
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, password, strlen(password));
            SHA256_Final(hash, &sha256);
            char hashedPassword[65];
            for(int j = 0; j < SHA256_DIGEST_LENGTH; ++j) {
                sprintf(hashedPassword + (j * 2), "%02x", hash[j]);
            }
            hashedPassword[64] = '\0';
            return strcmp(users[i].hashedPassword, hashedPassword) == 0;
        }
    }
    return 0;
}

int main() {
    // Test cases
    registerUser("user1", "password123");
    registerUser("user2", "password456");
    printf("%d\n", loginUser("user1", "password123")); // 1 (true)
    printf("%d\n", loginUser("user1", "wrongpassword")); // 0 (false)
    printf("%d\n", loginUser("user2", "password456")); // 1 (true)
    printf("%d\n", loginUser("nonexistent", "password")); // 0 (false)
    return 0;
}