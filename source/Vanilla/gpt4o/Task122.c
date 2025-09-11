#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    User users[MAX_USERS];
    int count;
} Task122;

void initTask(Task122* task) {
    task->count = 0;
}

bool signup(Task122* task, const char* username, const char* password) {
    for (int i = 0; i < task->count; i++) {
        if (strcmp(task->users[i].username, username) == 0) {
            return false; // Username already exists
        }
    }
    if (task->count < MAX_USERS) {
        strcpy(task->users[task->count].username, username);
        strcpy(task->users[task->count].password, password);
        task->count++;
        return true;
    }
    return false; // Maximum users reached
}

int main() {
    Task122 task;
    initTask(&task);

    // Test cases
    printf("%d\n", signup(&task, "user1", "pass1")); // 1
    printf("%d\n", signup(&task, "user2", "pass2")); // 1
    printf("%d\n", signup(&task, "user1", "pass3")); // 0
    printf("%d\n", signup(&task, "user3", "pass4")); // 1
    printf("%d\n", signup(&task, "user2", "pass5")); // 0

    return 0;
}