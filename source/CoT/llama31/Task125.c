#include <stdio.h>
#include <string.h>

void accessResource(const char* username, const char* password, const char* resource) {
    // Simulated user database for demonstration
    const char* validUsers[] = {"admin", "user", "guest"};
    const char* validPasswords[] = {"password123", "password123", "password123"};
    const char* accessibleResources[] = {"database", "file", "network"};

    // Security check: Validate user credentials
    int isValidUser = 0;
    for (int i = 0; i < 3; i++) {
        if (strcmp(username, validUsers[i]) == 0 && strcmp(password, validPasswords[i]) == 0) {
            isValidUser = 1;
            break;
        }
    }

    if (!isValidUser) {
        printf("Invalid username or password.\n");
        return;
    }

    // Check if the user has access to the requested resource
    int hasAccess = 0;
    for (int i = 0; i < 3; i++) {
        if (strcmp(resource, accessibleResources[i]) == 0) {
            hasAccess = 1;
            break;
        }
    }

    if (!hasAccess) {
        printf("You do not have access to this resource.\n");
        return;
    }

    // Grant access to the resource
    printf("Access granted to %s for user %s\n", resource, username);
}

int main() {
    // Test cases
    accessResource("admin", "password123", "database");
    accessResource("user", "password123", "file");
    accessResource("guest", "password123", "network");
    accessResource("admin", "wrongpassword", "database");
    accessResource("unknown", "password123", "database");
    return 0;
}