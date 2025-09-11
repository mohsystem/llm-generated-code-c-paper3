#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[100];
    char role[100];
} User;

bool hasPermission(User user, const char* permission) {
    if (strcmp(user.role, "admin") == 0) {
        return true;
    } else if (strcmp(user.role, "user") == 0) {
        return strcmp(permission, "read") == 0;
    } else {
        return false;
    }
}

int main() {
    // Test cases
    User user1 = {"John", "admin"};
    User user2 = {"Jane", "user"};

    printf("%d\n", hasPermission(user1, "create")); // 1 (true)
    printf("%d\n", hasPermission(user1, "read"));    // 1 (true)
    printf("%d\n", hasPermission(user1, "update"));  // 1 (true)
    printf("%d\n", hasPermission(user1, "delete")); // 1 (true)

    printf("%d\n", hasPermission(user2, "create")); // 0 (false)
    printf("%d\n", hasPermission(user2, "read"));    // 1 (true)
    printf("%d\n", hasPermission(user2, "update"));   // 0 (false)
    printf("%d\n", hasPermission(user2, "delete"));   // 0 (false)

    return 0;
}