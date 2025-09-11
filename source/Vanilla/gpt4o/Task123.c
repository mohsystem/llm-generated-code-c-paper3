#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char userId[50];
    char sessionId[50];
} Session;

typedef struct {
    Session sessions[MAX_USERS];
    int sessionCount;
} Task123;

void init(Task123* manager) {
    manager->sessionCount = 0;
}

void addSession(Task123* manager, const char* userId, const char* sessionId) {
    strcpy(manager->sessions[manager->sessionCount].userId, userId);
    strcpy(manager->sessions[manager->sessionCount].sessionId, sessionId);
    manager->sessionCount++;
}

const char* getSession(Task123* manager, const char* userId) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].userId, userId) == 0) {
            return manager->sessions[i].sessionId;
        }
    }
    return NULL;
}

void removeSession(Task123* manager, const char* userId) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].userId, userId) == 0) {
            for (int j = i; j < manager->sessionCount - 1; j++) {
                manager->sessions[j] = manager->sessions[j + 1];
            }
            manager->sessionCount--;
            return;
        }
    }
}

int main() {
    Task123 sessionManager;
    init(&sessionManager);
    addSession(&sessionManager, "user1", "session1");
    addSession(&sessionManager, "user2", "session2");
    printf("%s\n", getSession(&sessionManager, "user1")); // session1
    removeSession(&sessionManager, "user1");
    printf("%s\n", getSession(&sessionManager, "user1")); // (null)
    addSession(&sessionManager, "user3", "session3");
    printf("%s\n", getSession(&sessionManager, "user3")); // session3
    return 0;
}