#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_STRING 50

typedef struct {
    char username[MAX_STRING];
    char password[MAX_STRING];
} User;

User users[MAX_USERS];
int userCount = 0;

void addUser(char *username, char *password) {
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;
}

int resetPassword(char *username, char *oldPassword, char *newPassword) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, oldPassword) == 0) {
            strcpy(users[i].password, newPassword);
            return 1;
        }
    }
    return 0;
}

int main() {
    addUser("user1", "pass1");
    printf("%d\n", resetPassword("user1", "pass1", "newPass")); // Should print 1
    printf("%d\n", resetPassword("user1", "pass1", "anotherNewPass")); // Should print 0
    return 0;
}