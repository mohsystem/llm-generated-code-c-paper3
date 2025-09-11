#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERMISSIONS 10

typedef struct {
    char* username;
    char* permissions[MAX_PERMISSIONS];
    int permission_count;
} User;

User* createUser(char* username) {
    User* user = malloc(sizeof(User));
    user->username = username;
    user->permission_count = 0;
    return user;
}

void grantPermission(User* user, char* permission) {
    if (user->permission_count < MAX_PERMISSIONS) {
        user->permissions[user->permission_count++] = permission;
    }
}

void revokePermission(User* user, char* permission) {
    for (int i = 0; i < user->permission_count; i++) {
        if (strcmp(user->permissions[i], permission) == 0) {
            for (int j = i; j < user->permission_count - 1; j++) {
                user->permissions[j] = user->permissions[j + 1];
            }
            user->permission_count--;
            break;
        }
    }
}

int hasPermission(User* user, char* permission) {
    for (int i = 0; i < user->permission_count; i++) {
        if (strcmp(user->permissions[i], permission) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    User* user = createUser("JohnDoe");
    grantPermission(user, "READ");
    grantPermission(user, "WRITE");
    printf("%d\n", hasPermission(user, "READ"));  // Outputs: 1
    revokePermission(user, "READ");
    printf("%d\n", hasPermission(user, "READ"));  // Outputs: 0
    free(user);
    return 0;
}