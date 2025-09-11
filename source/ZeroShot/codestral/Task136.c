#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

struct User users[] = {{"user1", "password1"}, {"user2", "password2"}};

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char username[50], password[50];
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
    if (authenticate(username, password)) {
        printf("Authentication successful\n");
    } else {
        printf("Authentication failed\n");
    }
    return 0;
}