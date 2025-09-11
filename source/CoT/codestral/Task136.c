#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS] = {{"user1", "password1"}, {"user2", "password2"}};
int num_users = 2;

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    // Test cases
    printf("%d\n", authenticate("user1", "password1"));  // 1
    printf("%d\n", authenticate("user1", "wrongpassword"));  // 0
    printf("%d\n", authenticate("user3", "password3"));  // 0
    return 0;
}