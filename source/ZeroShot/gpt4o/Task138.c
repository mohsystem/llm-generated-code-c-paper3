#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PermissionNode {
    char permission[50];
    struct PermissionNode* next;
} PermissionNode;

typedef struct User {
    char username[50];
    PermissionNode* permissions;
    struct User* next;
} User;

User* users = NULL;

User* find_user(const char* username) {
    User* current = users;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void add_user(const char* username) {
    if (find_user(username) == NULL) {
        User* new_user = (User*)malloc(sizeof(User));
        strcpy(new_user->username, username);
        new_user->permissions = NULL;
        new_user->next = users;
        users = new_user;
    }
}

void remove_user(const char* username) {
    User** current = &users;
    while (*current != NULL) {
        if (strcmp((*current)->username, username) == 0) {
            User* temp = *current;
            *current = (*current)->next;
            free(temp);
            return;
        }
        current = &(*current)->next;
    }
}

void add_permission(const char* username, const char* permission) {
    User* user = find_user(username);
    if (user != NULL) {
        PermissionNode* new_permission = (PermissionNode*)malloc(sizeof(PermissionNode));
        strcpy(new_permission->permission, permission);
        new_permission->next = user->permissions;
        user->permissions = new_permission;
    }
}

void remove_permission(const char* username, const char* permission) {
    User* user = find_user(username);
    if (user != NULL) {
        PermissionNode** current = &user->permissions;
        while (*current != NULL) {
            if (strcmp((*current)->permission, permission) == 0) {
                PermissionNode* temp = *current;
                *current = (*current)->next;
                free(temp);
                return;
            }
            current = &(*current)->next;
        }
    }
}

int check_permission(const char* username, const char* permission) {
    User* user = find_user(username);
    if (user != NULL) {
        PermissionNode* current = user->permissions;
        while (current != NULL) {
            if (strcmp(current->permission, permission) == 0) {
                return 1;
            }
            current = current->next;
        }
    }
    return 0;
}

void free_users() {
    while (users != NULL) {
        User* temp = users;
        users = users->next;
        free(temp);
    }
}

int main() {
    // Test cases
    add_user("alice");
    add_permission("alice", "read");
    add_permission("alice", "write");
    
    add_user("bob");
    add_permission("bob", "execute");

    printf("%d\n", check_permission("alice", "read")); // 1 (true)
    printf("%d\n", check_permission("alice", "execute")); // 0 (false)
    printf("%d\n", check_permission("bob", "execute")); // 1 (true)
    printf("%d\n", check_permission("bob", "read")); // 0 (false)

    remove_permission("alice", "write");
    printf("%d\n", check_permission("alice", "write")); // 0 (false)

    free_users();
    return 0;
}