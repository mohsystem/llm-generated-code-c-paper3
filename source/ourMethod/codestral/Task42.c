#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int userCount = 0;

void addUser(const char* username, const char* password) {
    if (userCount < MAX_USERS) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].password, password);
        userCount++;
    }
}

bool authenticate(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return strcmp(users[i].password, password) == 0;
        }
    }
    return false;
}

int main() {
    addUser("user1", "password1");

    printf("%d\n", authenticate("user1", "password1"));  // 1
    printf("%d\n", authenticate("user1", "wrongpassword"));  // 0
    printf("%d\n", authenticate("user2", "password1"));  // 0

    return 0;
}