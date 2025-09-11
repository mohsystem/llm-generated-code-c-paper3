#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_HASH_LENGTH 65

typedef struct {
    char username[USERNAME_LENGTH];
    char passwordHash[PASSWORD_HASH_LENGTH];
} User;

User userStore[MAX_USERS];
int userCount = 0;

void hashPassword(const char *password, char *hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
    hashedPassword[64] = '\0';
}

int registerUser(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userStore[i].username, username) == 0) {
            return 0;
        }
    }
    strcpy(userStore[userCount].username, username);
    hashPassword(password, userStore[userCount].passwordHash);
    userCount++;
    return 1;
}

int loginUser(const char *username, const char *password) {
    char hashedPassword[PASSWORD_HASH_LENGTH];
    hashPassword(password, hashedPassword);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userStore[i].username, username) == 0 &&
            strcmp(userStore[i].passwordHash, hashedPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    printf("%d\n", registerUser("user1", "password1")); // 1
    printf("%d\n", registerUser("user1", "password2")); // 0
    printf("%d\n", loginUser("user1", "password1")); // 1
    printf("%d\n", loginUser("user1", "password2")); // 0
    printf("%d\n", loginUser("user2", "password1")); // 0
    return 0;
}