#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool hasPermission(char *user, char *permission) {
    // Replace with your permission logic
    if (strcmp(user, "admin") == 0) {
        return true;
    } else if (strcmp(user, "user1") == 0 && strcmp(permission, "read") == 0) {
        return true;
    }
    return false;
}

int main() {
    printf("%d\n", hasPermission("admin", "read")); // 1 (true)
    printf("%d\n", hasPermission("admin", "write")); // 1 (true)
    printf("%d\n", hasPermission("user1", "read")); // 1 (true)
    printf("%d\n", hasPermission("user1", "write")); // 0 (false)
    printf("%d\n", hasPermission("user2", "read")); // 0 (false)
    return 0;
}