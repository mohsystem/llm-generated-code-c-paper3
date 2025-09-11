#include <stdio.h>
#include <stdbool.h>

typedef enum {
    READ = 1,
    WRITE = 2,
    EXECUTE = 4
} Permission;

typedef struct {
    unsigned int permissions;
} Task138;

void addPermission(Task138 *user, Permission permission) {
    user->permissions |= permission;
}

void removePermission(Task138 *user, Permission permission) {
    user->permissions &= ~permission;
}

bool hasPermission(const Task138 *user, Permission permission) {
    return (user->permissions & permission) != 0;
}

int main() {
    Task138 user = {0};
    addPermission(&user, READ);
    printf("%d\n", hasPermission(&user, READ));  // 1 (true)
    printf("%d\n", hasPermission(&user, WRITE));  // 0 (false)
    removePermission(&user, READ);
    printf("%d\n", hasPermission(&user, READ));  // 0 (false)
    return 0;
}