#include <stdio.h>
#include <string.h>

// Note: This C implementation uses a simplified approach for demonstration
// and does not implement a real database.  A robust solution would require
// a database library or more complex data structures.

typedef struct {
    char name[100];
    char email[100];
    char password[100];
} User;

// Simulated database (limited capacity)
User users[100];
int userCount = 0;


void registerUser(const char *name, const char *email, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0) {
            printf("User with this email already exists.\n");
            return;
        }
    }

    if (userCount < 100) {
        strcpy(users[userCount].name, name);
        strcpy(users[userCount].email, email);
        strcpy(users[userCount].password, password);
        userCount++;
        printf("User registered successfully.\n");
    } else {
        printf("Database full. Cannot register user.\n");
    }
}


int main() {

    registerUser("John Doe", "john.doe@example.com", "password123");
    registerUser("Jane Doe", "jane.doe@example.com", "password456");
    registerUser("Peter Pan", "peter.pan@example.com", "password789");
    registerUser("John Doe", "john.doe@example.com", "new_password");
    registerUser("Alice Wonderland", "alice@example.com", "wonderland123");

    return 0;
}