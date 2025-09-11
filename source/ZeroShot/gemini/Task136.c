#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Simplified user database (insecure for real-world use)
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password123"},
    {"user2", "securepass"},
    {"admin", "adminpass"}
};
int num_users = sizeof(users) / sizeof(users[0]);

bool authenticate(const char *username, const char *password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    printf("%d\n", authenticate("user1", "password123")); // 1 (true)
    printf("%d\n", authenticate("user1", "wrongpass")); // 0 (false)
    printf("%d\n", authenticate("user3", "anypass")); // 0 (false)
    printf("%d\n", authenticate("admin", "adminpass")); // 1 (true)
    printf("%d\n", authenticate("user2", "securepass")); // 1 (true)

    return 0;
}