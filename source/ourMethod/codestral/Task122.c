#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is a simple implementation and does not handle errors or memory allocation properly.
// In a real application, you would need to handle these issues and also hash the passwords.

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int userCount = 0;

void signUp(const char* username, const char* password) {
    if (userCount < MAX_USERS) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].password, password);
        userCount++;
    }
}

int validateUser(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;  // Remove trailing newline

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;  // Remove trailing newline

    signUp(username, password);

    printf("Enter username to validate: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;  // Remove trailing newline

    printf("Enter password to validate: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;  // Remove trailing newline

    if (validateUser(username, password)) {
        printf("User validated successfully.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}