
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME 50
#define MAX_ROLE 20
#define PERMISSIONS_SIZE 3

typedef struct {
    char username[MAX_USERNAME];
    char role[MAX_ROLE];
    bool permissions[PERMISSIONS_SIZE];
} User;

User* createUser(const char* username, const char* role) {
    User* user = (User*)malloc(sizeof(User));
    if (user != NULL) {
        strncpy(user->username, username, MAX_USERNAME - 1);
        user->username[MAX_USERNAME - 1] = '\\0';
        strncpy(user->role, role, MAX_ROLE - 1);
        user->role[MAX_ROLE - 1] = '\\0';
        memset(user->permissions, 0, sizeof(bool) * PERMISSIONS_SIZE);
    }
    return user;
}

void setPermission(User* user, int permissionIndex, bool value) {
    if (user != NULL && permissionIndex >= 0 && permissionIndex < PERMISSIONS_SIZE) {
        user->permissions[permissionIndex] = value;
    }
}

bool checkPermission(User* user, int permissionIndex) {
    if (user != NULL && permissionIndex >= 0 && permissionIndex < PERMISSIONS_SIZE) {
        return user->permissions[permissionIndex];
    }
    return false;
}

bool validatePermission(User* user, int permissionIndex) {
    if (user == NULL) return false;
    return checkPermission(user, permissionIndex);
}

int main() {
    // Test case 1: Create admin user with all permissions
    User* admin = createUser("admin", "administrator");
    setPermission(admin, 0, true); // read
    setPermission(admin, 1, true); // write
    setPermission(admin, 2, true); // execute
    printf("Admin read permission: %d\\n", validatePermission(admin, 0));

    // Test case 2: Create regular user with only read permission
    User* user1 = createUser("user1", "regular");
    setPermission(user1, 0, true); // read only
    printf("User1 read permission: %d\\n", validatePermission(user1, 0));
    printf("User1 write permission: %d\\n", validatePermission(user1, 1));

    // Test case 3: Test invalid permission index
    User* user2 = createUser("user2", "regular");
    setPermission(user2, 5, true); // invalid index
    printf("User2 invalid permission: %d\\n", validatePermission(user2, 5));

    // Test case 4: Test null user
    printf("Null user permission: %d\\n", validatePermission(NULL, 0));

    // Test case 5: Create guest user with no permissions
    User* guest = createUser("guest", "guest");
    printf("Guest execute permission: %d\\n", validatePermission(guest, 2));

    // Clean up
    free(admin);
    free(user1);
    free(user2);
    free(guest);

    return 0;
}
