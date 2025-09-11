#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char passwordHash[65]; // 64 chars for SHA-256 hash + 1 for null terminator
} User;

typedef struct {
    User users[MAX_USERS];
    int count;
} Task42;

void initTask42(Task42* authSystem) {
    authSystem->count = 0;
}

int registerUser(Task42* authSystem, const char* username, const char* password) {
    for (int i = 0; i < authSystem->count; ++i) {
        if (strcmp(authSystem->users[i].username, username) == 0) {
            return 0;
        }
    }
    strcpy(authSystem->users[authSystem->count].username, username);
    // Simple hash for demonstration (not secure)
    sprintf(authSystem->users[authSystem->count].passwordHash, "%lu", hashFunction(password));
    authSystem->count++;
    return 1;
}

int authenticateUser(Task42* authSystem, const char* username, const char* password) {
    for (int i = 0; i < authSystem->count; ++i) {
        if (strcmp(authSystem->users[i].username, username) == 0 &&
            strcmp(authSystem->users[i].passwordHash, password) == 0) {
            return 1;
        }
    }
    return 0;
}

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

int main() {
    Task42 authSystem;
    initTask42(&authSystem);
    
    printf("%d\n", registerUser(&authSystem, "user1", "password1")); // True
    printf("%d\n", authenticateUser(&authSystem, "user1", "password1")); // True
    printf("%d\n", authenticateUser(&authSystem, "user1", "wrongpassword")); // False
    printf("%d\n", registerUser(&authSystem, "user1", "password1")); // False
    printf("%d\n", authenticateUser(&authSystem, "user2", "password2")); // False

    return 0;
}