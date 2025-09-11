#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
};

struct User userDatabase[MAX_USERS];
int userCount = 0;

void signUp(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            printf("Username already exists.\n");
            return;
        }
    }

    if (userCount < MAX_USERS) {
        strcpy(userDatabase[userCount].username, username);
        char* hashedPassword = hashPassword(password);
        strcpy(userDatabase[userCount].hashedPassword, hashedPassword);
        free(hashedPassword);
        userCount++;
        printf("User created successfully.\n");
    } else {
        printf("User database is full.\n");
    }
}

char* hashPassword(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    char* hashedPassword = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hashedPassword;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    signUp(username, password);

    return 0;
}