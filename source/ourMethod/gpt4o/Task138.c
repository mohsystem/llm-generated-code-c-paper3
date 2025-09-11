#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_PERMISSIONS 10
#define MAX_NAME_LEN 50

typedef struct {
    char username[MAX_NAME_LEN];
    char permissions[MAX_PERMISSIONS][MAX_NAME_LEN];
    int permission_count;
} User;

typedef struct {
    User users[MAX_USERS];
    int user_count;
} Task138;

void initTask138(Task138 *system) {
    system->user_count = 0;
}

void addUser(Task138 *system, const char *username) {
    if (system->user_count < MAX_USERS) {
        strcpy(system->users[system->user_count].username, username);
        system->users[system->user_count].permission_count = 0;
        system->user_count++;
    }
}

void removeUser(Task138 *system, const char *username) {
    for (int i = 0; i < system->user_count; i++) {
        if (strcmp(system->users[i].username, username) == 0) {
            for (int j = i; j < system->user_count - 1; j++) {
                system->users[j] = system->users[j + 1];
            }
            system->user_count--;
            break;
        }
    }
}

void grantPermission(Task138 *system, const char *username, const char *permission) {
    for (int i = 0; i < system->user_count; i++) {
        if (strcmp(system->users[i].username, username) == 0) {
            if (system->users[i].permission_count < MAX_PERMISSIONS) {
                strcpy(system->users[i].permissions[system->users[i].permission_count], permission);
                system->users[i].permission_count++;
            }
            break;
        }
    }
}

void revokePermission(Task138 *system, const char *username, const char *permission) {
    for (int i = 0; i < system->user_count; i++) {
        if (strcmp(system->users[i].username, username) == 0) {
            for (int j = 0; j < system->users[i].permission_count; j++) {
                if (strcmp(system->users[i].permissions[j], permission) == 0) {
                    for (int k = j; k < system->users[i].permission_count - 1; k++) {
                        strcpy(system->users[i].permissions[k], system->users[i].permissions[k + 1]);
                    }
                    system->users[i].permission_count--;
                    break;
                }
            }
            break;
        }
    }
}

bool checkPermission(Task138 *system, const char *username, const char *permission) {
    for (int i = 0; i < system->user_count; i++) {
        if (strcmp(system->users[i].username, username) == 0) {
            for (int j = 0; j < system->users[i].permission_count; j++) {
                if (strcmp(system->users[i].permissions[j], permission) == 0) {
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

int main() {
    Task138 system;
    initTask138(&system);

    addUser(&system, "alice");
    addUser(&system, "bob");

    grantPermission(&system, "alice", "read");
    grantPermission(&system, "bob", "write");

    // Test cases
    printf("%d\n", checkPermission(&system, "alice", "read")); // true
    printf("%d\n", checkPermission(&system, "alice", "write")); // false
    printf("%d\n", checkPermission(&system, "bob", "write")); // true
    revokePermission(&system, "bob", "write");
    printf("%d\n", checkPermission(&system, "bob", "write")); // false
    removeUser(&system, "alice");
    printf("%d\n", checkPermission(&system, "alice", "read")); // false

    return 0;
}