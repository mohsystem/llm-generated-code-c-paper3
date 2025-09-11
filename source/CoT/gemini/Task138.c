#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note: This C implementation uses a simplified approach for demonstration 
// and might not be as robust as the C++/Java/Python versions in terms of 
// memory management or error handling for larger datasets.

#define MAX_USERS 10
#define MAX_PERMISSIONS 10
#define MAX_PERMISSION_LENGTH 20

typedef struct {
    char user[50];
    char permissions[MAX_PERMISSIONS][MAX_PERMISSION_LENGTH];
    int num_permissions;
} UserPermissions;

UserPermissions users[MAX_USERS];
int num_users = 0;


int find_user(const char *user) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].user, user) == 0) {
            return i;
        }
    }
    return -1;
}

void add_user(const char *user) {
    if (num_users < MAX_USERS && find_user(user) == -1) {
        strcpy(users[num_users].user, user);
        users[num_users].num_permissions = 0;
        num_users++;
    }
}

void add_permission(const char *user, const char *permission) {
    int index = find_user(user);
    if (index != -1 && users[index].num_permissions < MAX_PERMISSIONS) {
        strcpy(users[index].permissions[users[index].num_permissions], permission);
        users[index].num_permissions++;
    }
}

void remove_permission(const char *user, const char *permission) {
    int index = find_user(user);
    if (index != -1) {
        for (int i = 0; i < users[index].num_permissions; i++) {
            if (strcmp(users[index].permissions[i], permission) == 0) {
                // Shift remaining permissions
                for (int j = i; j < users[index].num_permissions - 1; j++) {
                    strcpy(users[index].permissions[j], users[index].permissions[j + 1]);
                }
                users[index].num_permissions--;
                break;
            }
        }
    }
}

int has_permission(const char *user, const char *permission) {
    int index = find_user(user);
    if (index != -1) {
        for (int i = 0; i < users[index].num_permissions; i++) {
            if (strcmp(users[index].permissions[i], permission) == 0) {
                return 1; 
            }
        }
    }
    return 0; 
}



int main() {
    // Test cases (similar to other languages)
    add_user("alice");
    add_permission("alice", "read");
    add_permission("alice", "write");
    printf("%d\n", has_permission("alice", "read")); // 1 (true)
    printf("%d\n", has_permission("alice", "execute")); // 0 (false)

    // ... (Add other test cases similar to C++, Java, Python)
    return 0;
}