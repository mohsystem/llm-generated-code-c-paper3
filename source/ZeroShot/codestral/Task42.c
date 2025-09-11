#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    char* username;
    char* password;
    struct User* next;
} User;

User* users = NULL;

void registerUser(const char* username, const char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    newUser->username = strdup(username);
    newUser->password = strdup(password);
    newUser->next = users;
    users = newUser;
}

int authenticateUser(const char* username, const char* password) {
    User* current = users;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return strcmp(current->password, password) == 0;
        }
        current = current->next;
    }
    return 0;
}

int main() {
    // Test cases
    registerUser("user1", "password1");
    registerUser("user2", "password2");

    printf("%d\n", authenticateUser("user1", "password1")); // 1
    printf("%d\n", authenticateUser("user2", "wrong_password")); // 0

    return 0;
}