#include <stdio.h>
#include <string.h>

const char* accessResource(const char *role) {
    struct {
        const char *role;
        const char *resource;
    } resources[] = {
        {"admin", "Admin Resource"},
        {"user", "User Resource"},
        {"guest", "Guest Resource"}
    };

    for (int i = 0; i < 3; i++) {
        if (strcmp(role, resources[i].role) == 0) {
            return resources[i].resource;
        }
    }
    return "Access Denied";
}

int main() {
    const char* roles[] = {"admin", "user", "guest", "invalid", "user"};
    for (int i = 0; i < 5; i++) {
        printf("Role: %s -> %s\n", roles[i], accessResource(roles[i]));
    }
    return 0;
}