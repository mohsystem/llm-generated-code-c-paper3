#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char username[100];
    char password[100];
} User;

User users[10];
int userCount = 0;

void registerUser(const char* username, const char* password) {
    if (userCount >= 10) {
        printf("Maximum users reached.\n");
        return;
    }
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists.\n");
            return;
        }
    }
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, hashPassword(password));
    printf("User registered successfully.\n");
    userCount++;
}

void loginUser(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, hashPassword(password)) == 0) {
                printf("Login successful.\n");
            } else {
                printf("Incorrect password.\n");
            }
            return;
        }
    }
    printf("Username does not exist.\n");
}

char* hashPassword(const char* password) {
    static char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hashedPassword;
}

void testCases() {
    registerUser("user1", "password1");
    registerUser("user2", "password2");
    loginUser("user1", "password1");
    loginUser("user1", "wrongpassword");
    loginUser("user3", "password3");
}

int main() {
    testCases();
    return 0;
}