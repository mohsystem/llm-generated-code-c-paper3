#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int userCount = 0;

void registerUser(const char* username, const char* password) {
    if (userCount >= MAX_USERS) {
        return;
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;
}

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }

    return 0;
}

int main() {
    registerUser("user1", "pass1");
    registerUser("user2", "pass2");

    printf("%d\n", authenticate("user1", "pass1")); // 1 (true)
    printf("%d\n", authenticate("user2", "wrongPass")); // 0 (false)
    printf("%d\n", authenticate("nonexistentUser", "pass")); // 0 (false)

    return 0;
}