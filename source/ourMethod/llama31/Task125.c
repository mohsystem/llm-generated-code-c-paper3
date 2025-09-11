#include <stdio.h>
#include <string.h>

#define MAX_RESOURCES 3
#define MAX_ACCESS_LEVELS 3

typedef struct {
    char resources[MAX_RESOURCES][20];
    char accessLevels[MAX_ACCESS_LEVELS][20];
} Task125;

void initTask125(Task125* task) {
    strcpy(task->resources[0], "Resource1");
    strcpy(task->resources[1], "Resource2");
    strcpy(task->resources[2], "Resource3");

    strcpy(task->accessLevels[0], "Admin");
    strcpy(task->accessLevels[1], "User");
    strcpy(task->accessLevels[2], "Guest");
}

int accessResource(const Task125* task, const char* user, const char* resource) {
    // Check if user and resource are not null
    if (user == NULL || resource == NULL) {
        return 0;
    }

    // Simulate access control
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (strcmp(task->resources[i], resource) == 0) {
            // Simple access control logic for demonstration
            if (strcmp(user, "Admin") == 0) {
                return 1;
            } else if (strcmp(user, "User") == 0 && strcmp(task->resources[i], "Resource1") != 0) {
                return 1;
            } else if (strcmp(user, "Guest") == 0 && strcmp(task->resources[i], "Resource1") != 0 && strcmp(task->resources[i], "Resource2") != 0) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    Task125 task;
    initTask125(&task);

    const char* testCases[][2] = {
        {"Admin", "Resource1"},
        {"User", "Resource2"},
        {"Guest", "Resource3"},
        {"InvalidUser", "Resource1"},  // Invalid user
        {"Admin", "InvalidResource"}  // Invalid resource
    };

    for (int i = 0; i < 5; i++) {
        printf("User: %s, Resource: %s\n", testCases[i][0], testCases[i][1]);
        if (accessResource(&task, testCases[i][0], testCases[i][1])) {
            printf("Access granted.\n");
        } else {
            printf("Access denied.\n");
        }
        printf("\n");
    }

    return 0;
}