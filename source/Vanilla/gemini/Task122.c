#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Basic implementation using a fixed-size array. Not ideal for real-world scenarios.
#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int num_users = 0;


void signup(const char *username, const char *password) {
    if (num_users < MAX_USERS) {
        strcpy(users[num_users].username, username);
        strcpy(users[num_users].password, password);
        num_users++;
    } else {
        printf("Maximum number of users reached.\n");
    }
}

int main() {
    signup("user1", "password123");
    signup("user2", "securepass");
    signup("user3", "mypassword");
    signup("user4", "complexpass");
    signup("user5", "easy123");

    printf("User passwords stored:\n");
    for (int i = 0; i < num_users; i++) {
        printf("Username: %s, Password: %s\n", users[i].username, users[i].password);
    }

    return 0;
}