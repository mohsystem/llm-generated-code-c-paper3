#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

typedef struct {
    char username[100];
    char password[100];
} User;

User users[100];
int userCount = 0;

void registerUser() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, hashedPassword);
    userCount++;
    printf("Registration successful\n");
}

void loginUser() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, hashedPassword) == 0) {
            printf("Login successful\n");
            return;
        }
    }
    printf("Invalid credentials\n");
}

void testCases() {
    // Test case 1: Register a user
    registerUser();
    // Test case 2: Login with correct credentials
    loginUser();
    // Test case 3: Login with incorrect credentials
    loginUser();
    // Test case 4: Register another user
    registerUser();
    // Test case 5: Login with correct credentials for the second user
    loginUser();
}

int main() {
    testCases();
    return 0;
}