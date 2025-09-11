#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 65 // SHA-256 hash length is 64 + 1 for null-terminator

typedef struct {
    char username[USERNAME_LENGTH];
    char hashed_password[PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void hashPassword(const char *password, char *outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
}

int signup(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return 0; // User already exists
        }
    }
    if (user_count >= MAX_USERS) {
        return 0; // User list is full
    }
    strncpy(users[user_count].username, username, USERNAME_LENGTH);
    hashPassword(password, users[user_count].hashed_password);
    user_count++;
    return 1;
}

int main() {
    printf("%d\n", signup("user1", "pass123")); // 1
    printf("%d\n", signup("user2", "123pass")); // 1
    printf("%d\n", signup("user1", "newpass")); // 0
    printf("%d\n", signup("user3", "mySecret")); // 1
    printf("%d\n", signup("user4", "anotherPass")); // 1
    return 0;
}