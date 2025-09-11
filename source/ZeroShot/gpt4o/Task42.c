#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char passwordHash[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

User userDatabase[MAX_USERS];
int userCount = 0;

void registerUser(const char *username, const char *password) {
    if (userCount >= MAX_USERS) return;
    strcpy(userDatabase[userCount].username, username);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(userDatabase[userCount].passwordHash + (i * 2), "%02x", hash[i]);
    }

    userCount++;
}

int authenticateUser(const char *username, const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);

    char passwordHash[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(passwordHash + (i * 2), "%02x", hash[i]);
    }

    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            return strcmp(userDatabase[i].passwordHash, passwordHash) == 0;
        }
    }
    return 0;
}

int main() {
    registerUser("user1", "password1");
    registerUser("user2", "password2");
    registerUser("user3", "password3");
    registerUser("user4", "password4");
    registerUser("user5", "password5");

    printf("%d\n", authenticateUser("user1", "password1")); // 1
    printf("%d\n", authenticateUser("user2", "wrongpass")); // 0
    printf("%d\n", authenticateUser("user3", "password3")); // 1
    printf("%d\n", authenticateUser("user4", "password4")); // 1
    printf("%d\n", authenticateUser("user5", "wrongpass")); // 0

    return 0;
}