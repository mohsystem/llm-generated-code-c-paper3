#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Simplified user database (in real app, use secure storage)
struct User {
    char username[50];
    char password[50];
};

struct User users[] = {
    {"john", "password123"},
    {"jane", "securepass"},
    {"admin", "adminpass"}
};
int num_users = sizeof(users) / sizeof(users[0]);


bool authenticate(const char *username, const char *password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0) {
            return strcmp(password, users[i].password) == 0;
        }
    }
    return false; // User not found
}

int main() {
    printf("%d\n", authenticate("john", "password123"));  // 1 (true)
    printf("%d\n", authenticate("jane", "wrongpass"));   // 0 (false)
    printf("%d\n", authenticate("peter", "pass123"));   // 0 (false)
    printf("%d\n", authenticate("admin", "adminpass"));  // 1 (true)
    printf("%d\n", authenticate("john", "wrongpassword")); // 0 (false)
    return 0;
}