// C implementation
// Note: C does not support object-oriented programming directly, so this is a simplified version.

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    char role[100];
} User;

typedef struct PermissionHandler {
    int (*checkPermission)(const User*, const char*);
    struct PermissionHandler* nextHandler;
} PermissionHandler;

int roleCheckPermission(const User* user, const char* action) {
    if (strcmp(user->role, "admin") == 0 && strcmp(action, "write") == 0) {
        return 1;
    }
    return 0;
}

int actionCheckPermission(const User* user, const char* action) {
    if (strcmp(user->role, "viewer") == 0 && strcmp(action, "read") == 0) {
        return 1;
    }
    return 0;
}

void setNextHandler(PermissionHandler* handler, PermissionHandler* next) {
    handler->nextHandler = next;
}

int checkPermission(PermissionHandler* handler, const User* user, const char* action) {
    if (handler->checkPermission(user, action)) {
        return 1;
    }
    if (handler->nextHandler) {
        return checkPermission(handler->nextHandler, user, action);
    }
    return 0;
}

int main() {
    // Setting up the chain of handlers
    PermissionHandler roleHandler;
    PermissionHandler actionHandler;

    roleHandler.checkPermission = roleCheckPermission;
    actionHandler.checkPermission = actionCheckPermission;

    setNextHandler(&roleHandler, &actionHandler);

    // Test cases
    User adminUser = {"Admin", "admin"};
    User viewerUser = {"Viewer", "viewer"};

    printf("Admin trying to write: %s\n", checkPermission(&roleHandler, &adminUser, "write") ? "true" : "false");
    printf("Viewer trying to read: %s\n", checkPermission(&roleHandler, &viewerUser, "read") ? "true" : "false");
    printf("Admin trying to read: %s\n", checkPermission(&roleHandler, &adminUser, "read") ? "true" : "false");
    printf("Viewer trying to write: %s\n", checkPermission(&roleHandler, &viewerUser, "write") ? "true" : "false");
    printf("Admin trying to delete: %s\n", checkPermission(&roleHandler, &adminUser, "delete") ? "true" : "false");

    return 0;
}