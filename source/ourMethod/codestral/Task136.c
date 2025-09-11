#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct Task136 {
    struct User users[MAX_USERS];
    int userCount;
};

struct Task136* Task136_create() {
    struct Task136* auth = (struct Task136*)malloc(sizeof(struct Task136));
    if (auth == NULL) {
        return NULL;
    }

    // Populate the users array with some user credentials for testing
    strcpy(auth->users[0].username, "user1");
    strcpy(auth->users[0].password, "password1");
    strcpy(auth->users[1].username, "user2");
    strcpy(auth->users[1].password, "password2");
    auth->userCount = 2;

    return auth;
}

bool Task136_authenticate(struct Task136* auth, const char* username, const char* password) {
    if (username == NULL || password == NULL) {
        return false;
    }

    for (int i = 0; i < auth->userCount; i++) {
        if (strcmp(auth->users[i].username, username) == 0) {
            // Compare the passwords using a secure method
            return secureCompare(password, auth->users[i].password);
        }
    }

    return false;
}

bool secureCompare(const char* a, const char* b) {
    if (strlen(a) != strlen(b)) {
        return false;
    }

    int result = 0;
    for (size_t i = 0; i < strlen(a); i++) {
        result |= a[i] ^ b[i];
    }

    return result == 0;
}

int main() {
    struct Task136* auth = Task136_create();
    if (auth == NULL) {
        return 1;
    }

    // Test cases
    printf("%d\n", Task136_authenticate(auth, "user1", "password1")); // Expected: 1
    printf("%d\n", Task136_authenticate(auth, "user1", "wrong_password")); // Expected: 0
    printf("%d\n", Task136_authenticate(auth, "nonexistent_user", "password")); // Expected: 0
    printf("%d\n", Task136_authenticate(auth, NULL, "password")); // Expected: 0
    printf("%d\n", Task136_authenticate(auth, "user1", NULL)); // Expected: 0

    free(auth);
    return 0;
}