#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PERMISSIONS 100

typedef struct {
    char* permissions[MAX_PERMISSIONS];
    int size;
} Task138;

void grantPermission(Task138* user, char* permission) {
    if (user->size < MAX_PERMISSIONS) {
        user->permissions[user->size] = strdup(permission);
        user->size++;
    }
}

void revokePermission(Task138* user, char* permission) {
    for (int i = 0; i < user->size; i++) {
        if (strcmp(user->permissions[i], permission) == 0) {
            free(user->permissions[i]);
            for (int j = i; j < user->size - 1; j++) {
                user->permissions[j] = user->permissions[j + 1];
            }
            user->size--;
            break;
        }
    }
}

bool hasPermission(Task138* user, char* permission) {
    for (int i = 0; i < user->size; i++) {
        if (strcmp(user->permissions[i], permission) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    Task138 user = { .size = 0 };

    grantPermission(&user, "READ");
    grantPermission(&user, "WRITE");

    printf("%d\n", hasPermission(&user, "READ")); // 1 (true)
    printf("%d\n", hasPermission(&user, "EXECUTE")); // 0 (false)

    revokePermission(&user, "READ");

    printf("%d\n", hasPermission(&user, "READ")); // 0 (false)

    return 0;
}