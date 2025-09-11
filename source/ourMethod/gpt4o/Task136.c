#include <stdio.h>
#include <string.h>

typedef struct {
    const char* username;
    const char* password;
} User;

int authenticate(const User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    User users[] = {
        {"user1", "password1"},
        {"user2", "password2"},
        {"user3", "password3"},
        {"user4", "password4"},
        {"user5", "password5"}
    };

    const int userCount = sizeof(users) / sizeof(users[0]);

    const char* testCases[][2] = {
        {"user1", "password1"},
        {"user2", "wrongpassword"},
        {"user3", "password3"},
        {"invalidUser", "password"},
        {"user4", "password4"}
    };

    for (int i = 0; i < 5; ++i) {
        printf("Authenticating %s: %s\n", testCases[i][0], authenticate(users, userCount, testCases[i][0], testCases[i][1]) ? "True" : "False");
    }

    return 0;
}