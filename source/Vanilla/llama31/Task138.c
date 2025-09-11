#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_ROLES 100
#define MAX_PRIVILEGES 100

typedef struct {
    char username[50];
    char role[50];
} User;

typedef struct {
    char role[50];
    char privilege[50];
    bool allowed;
} Privilege;

User users[MAX_USERS];
int userCount = 0;

Privilege privileges[MAX_PRIVILEGES];
int privilegeCount = 0;

void addUser(const char* username, const char* role) {
    if (userCount < MAX_USERS) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].role, role);
        userCount++;
    }
}

void assignPrivilege(const char* role, const char* privilege, bool allowed) {
    if (privilegeCount < MAX_PRIVILEGES) {
        strcpy(privileges[privilegeCount].role, role);
        strcpy(privileges[privilegeCount].privilege, privilege);
        privileges[privilegeCount].allowed = allowed;
        privilegeCount++;
    }
}

bool checkPrivilege(const char* username, const char* privilege) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            for (int j = 0; j < privilegeCount; j++) {
                if (strcmp(privileges[j].role, users[i].role) == 0 && strcmp(privileges[j].privilege, privilege) == 0) {
                    return privileges[j].allowed;
                }
            }
        }
    }
    return false;
}

int main() {
    // Test cases
    addUser("admin", "administrator");
    addUser("user", "standard");
    addUser("guest", "guest");

    assignPrivilege("administrator", "create", true);
    assignPrivilege("administrator", "read", true);
    assignPrivilege("administrator", "update", true);
    assignPrivilege("administrator", "delete", true);

    assignPrivilege("standard", "read", true);
    assignPrivilege("standard", "update", true);

    assignPrivilege("guest", "read", true);

    printf("%d\n", checkPrivilege("admin", "create")); // 1 (true)
    printf("%d\n", checkPrivilege("user", "create")); // 0 (false)
    printf("%d\n", checkPrivilege("guest", "update")); // 0 (false)
    printf("%d\n", checkPrivilege("admin", "read")); // 1 (true)
    printf("%d\n", checkPrivilege("user", "read")); // 1 (true)

    return 0;
}