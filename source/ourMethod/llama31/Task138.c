#include <stdio.h>
#include <string.h>

typedef struct Role {
    char name[20];
    char* permissions[4];
} Role;

typedef struct User {
    char username[20];
    char role[20];
    Role roles[2];
} User;

void initRoles(User* user) {
    strcpy(user->roles[0].name, "admin");
    user->roles[0].permissions[0] = "create";
    user->roles[0].permissions[1] = "read";
    user->roles[0].permissions[2] = "update";
    user->roles[0].permissions[3] = "delete";

    strcpy(user->roles[1].name, "user");
    user->roles[1].permissions[0] = "read";
}

int hasPermission(User* user, const char* permission) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(user->roles[i].name, user->role) == 0) {
            for (int j = 0; j < 4; j++) {
                if (user->roles[i].permissions[j] != NULL && strcmp(user->roles[i].permissions[j], permission) == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    // Test cases
    User user1;
    strcpy(user1.username, "user1");
    strcpy(user1.role, "admin");
    initRoles(&user1);

    User user2;
    strcpy(user2.username, "user2");
    strcpy(user2.role, "user");
    initRoles(&user2);

    printf("%d\n", hasPermission(&user1, "create")); // 1
    printf("%d\n", hasPermission(&user1, "read"));   // 1
    printf("%d\n", hasPermission(&user1, "update")); // 1
    printf("%d\n", hasPermission(&user1, "delete")); // 1

    printf("%d\n", hasPermission(&user2, "create")); // 0
    printf("%d\n", hasPermission(&user2, "read"));   // 1
    printf("%d\n", hasPermission(&user2, "update")); // 0
    printf("%d\n", hasPermission(&user2, "delete")); // 0

    return 0;
}