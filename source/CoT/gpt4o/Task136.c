#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"user3", "password3"}
};

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    const char* testCases[][2] = {
        {"user1", "password1"},
        {"user2", "wrongpassword"},
        {"nonexistent", "password"},
        {"user3", "password3"},
        {"user1", "password123"}
    };

    for (int i = 0; i < sizeof(testCases)/sizeof(testCases[0]); i++) {
        printf("Authentication result for %s: %d\n", testCases[i][0], authenticate(testCases[i][0], testCases[i][1]));
    }

    return 0;
}