#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char hashedPassword[65];
} User;

User userDatabase[MAX_USERS];
int userCount = 0;

int signUp(const char *username, const char *password) {
    if (username == NULL || password == NULL || strlen(username) == 0 || strlen(password) == 0) {
        return 0;
    }
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            return 0; // Username already exists
        }
    }
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    char hashedPassword[65];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
    strcpy(userDatabase[userCount].username, username);
    strcpy(userDatabase[userCount].hashedPassword, hashedPassword);
    userCount++;
    return 1;
}

int main() {
    printf("%d\n", signUp("user1", "password123")); // Expected: 1 (true)
    printf("%d\n", signUp("user1", "anotherPassword")); // Expected: 0 (false, duplicate username)
    printf("%d\n", signUp("user2", "pass")); // Expected: 1 (true)
    printf("%d\n", signUp("", "password")); // Expected: 0 (false, invalid username)
    printf("%d\n", signUp("user3", "")); // Expected: 0 (false, invalid password)
    return 0;
}