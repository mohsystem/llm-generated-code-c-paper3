#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int userCount = 0;

void registerUser(char* username, char* password) {
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;
}

bool authenticateUser(char* username, char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    registerUser("user1", "password1");
    printf("%d\n", authenticateUser("user1", "password1"));  // 1 (true)
    printf("%d\n", authenticateUser("user1", "wrongPassword"));  // 0 (false)
    return 0;
}