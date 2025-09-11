#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_PERMISSIONS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    char permissions[MAX_PERMISSIONS][MAX_NAME_LENGTH];
    int permission_count;
} User;

typedef struct {
    User users[MAX_USERS];
    int user_count;
} Task138;

void init(Task138 *task) {
    task->user_count = 0;
}

void addUser(Task138 *task, const char *user) {
    if (task->user_count < MAX_USERS) {
        strcpy(task->users[task->user_count].name, user);
        task->users[task->user_count].permission_count = 0;
        task->user_count++;
    }
}

void grantPermission(Task138 *task, const char *user, const char *permission) {
    for (int i = 0; i < task->user_count; ++i) {
        if (strcmp(task->users[i].name, user) == 0) {
            if (task->users[i].permission_count < MAX_PERMISSIONS) {
                strcpy(task->users[i].permissions[task->users[i].permission_count], permission);
                task->users[i].permission_count++;
            }
            break;
        }
    }
}

void revokePermission(Task138 *task, const char *user, const char *permission) {
    for (int i = 0; i < task->user_count; ++i) {
        if (strcmp(task->users[i].name, user) == 0) {
            for (int j = 0; j < task->users[i].permission_count; ++j) {
                if (strcmp(task->users[i].permissions[j], permission) == 0) {
                    for (int k = j; k < task->users[i].permission_count - 1; ++k) {
                        strcpy(task->users[i].permissions[k], task->users[i].permissions[k + 1]);
                    }
                    task->users[i].permission_count--;
                    break;
                }
            }
            break;
        }
    }
}

int checkPermission(Task138 *task, const char *user, const char *permission) {
    for (int i = 0; i < task->user_count; ++i) {
        if (strcmp(task->users[i].name, user) == 0) {
            for (int j = 0; j < task->users[i].permission_count; ++j) {
                if (strcmp(task->users[i].permissions[j], permission) == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    Task138 task;
    init(&task);
    
    addUser(&task, "alice");
    addUser(&task, "bob");
    
    grantPermission(&task, "alice", "read");
    grantPermission(&task, "alice", "write");
    grantPermission(&task, "bob", "read");
    
    printf("%d\n", checkPermission(&task, "alice", "read")); // 1
    printf("%d\n", checkPermission(&task, "alice", "write")); // 1
    printf("%d\n", checkPermission(&task, "bob", "write")); // 0
    
    revokePermission(&task, "alice", "write");
    
    printf("%d\n", checkPermission(&task, "alice", "write")); // 0
    
    return 0;
}