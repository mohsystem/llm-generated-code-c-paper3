#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Implement a simple hash table for user permissions (for demonstration).  
// In a real-world application, use a more robust hash table implementation.

#define MAX_USERS 100
#define MAX_PERMISSIONS 50

typedef struct {
    char user[50];
    char permissions[MAX_PERMISSIONS][50];
    int num_permissions;
} UserPermissions;

UserPermissions user_permissions[MAX_USERS];
int num_users = 0;


int find_user(const char *user) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(user_permissions[i].user, user) == 0) {
            return i;
        }
    }
    return -1;
}

void add_user(const char *user) {
    if (num_users < MAX_USERS && find_user(user) == -1) {
        strcpy(user_permissions[num_users].user, user);
        user_permissions[num_users].num_permissions = 0;
        num_users++;
    }
}


void remove_user(const char *user) {
  int index = find_user(user);
  if (index != -1) {
    // Shift elements to remove the user
    for (int i = index; i < num_users - 1; i++) {
      user_permissions[i] = user_permissions[i + 1];
    }
    num_users--;
  }
}

void add_permission(const char *user, const char *permission) {
    int index = find_user(user);
    if (index != -1) {
      if (user_permissions[index].num_permissions < MAX_PERMISSIONS) {
        strcpy(user_permissions[index].permissions[user_permissions[index].num_permissions], permission);
        user_permissions[index].num_permissions++;
      }
    }
}

void remove_permission(const char *user, const char *permission) {
    int index = find_user(user);
    if (index != -1) {
        for (int i = 0; i < user_permissions[index].num_permissions; i++) {
            if (strcmp(user_permissions[index].permissions[i], permission) == 0) {
                // Shift remaining permissions
                for (int j = i; j < user_permissions[index].num_permissions - 1; j++) {
                    strcpy(user_permissions[index].permissions[j], user_permissions[index].permissions[j + 1]);
                }
                user_permissions[index].num_permissions--;
                break; 
            }
        }
    }
}


bool has_permission(const char *user, const char *permission) {
    int index = find_user(user);
    if (index != -1) {
        for (int i = 0; i < user_permissions[index].num_permissions; i++) {
            if (strcmp(user_permissions[index].permissions[i], permission) == 0) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    add_user("alice");
    add_permission("alice", "read");
    add_permission("alice", "write");
    printf("%s\n", has_permission("alice", "read") ? "true" : "false"); // true
    printf("%s\n", has_permission("alice", "execute") ? "true" : "false"); // false

    remove_permission("alice", "write");
    printf("%s\n", has_permission("alice", "write") ? "true" : "false"); // false

    add_user("bob");
    add_permission("bob", "execute");
    printf("%s\n", has_permission("bob", "execute") ? "true" : "false"); // true

    remove_user("alice");
    printf("%s\n", has_permission("alice", "read") ? "true" : "false"); // false

    return 0;
}