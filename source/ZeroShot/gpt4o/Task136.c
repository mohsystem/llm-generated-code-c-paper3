#include <stdio.h>
#include <string.h>

typedef struct {
    const char *username;
    const char *password;
} User;

User users[] = {
    {"user1", "password123"},
    {"user2", "pass456"},
    {"admin", "adminpass"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    // Test cases
    printf("%d\n", authenticate("user1", "password123")); // 1
    printf("%d\n", authenticate("user2", "pass456")); // 1
    printf("%d\n", authenticate("admin", "adminpass")); // 1
    printf("%d\n", authenticate("user1", "wrongpass")); // 0
    printf("%d\n", authenticate("unknown", "password")); // 0
    return 0;
}