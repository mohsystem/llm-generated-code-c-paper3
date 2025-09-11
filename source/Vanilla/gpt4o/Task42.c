#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char password[100];
} User;

User userDatabase[100];
int userCount = 0;

int registerUser(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            return 0;
        }
    }
    strcpy(userDatabase[userCount].username, username);
    strcpy(userDatabase[userCount].password, password);
    userCount++;
    return 1;
}

int login(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0 && strcmp(userDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    printf("%d\n", registerUser("user1", "pass1")); // 1
    printf("%d\n", registerUser("user1", "pass1")); // 0
    printf("%d\n", login("user1", "pass1")); // 1
    printf("%d\n", login("user2", "pass2")); // 0
    printf("%d\n", login("user1", "wrongpass")); // 0
    return 0;
}