#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char sessionId[50];
    char userId[50];
} Session;

typedef struct {
    Session sessions[100];
    int count;
} Task53;

void init(Task53* manager) {
    manager->count = 0;
}

char* createSession(Task53* manager, const char* userId) {
    char* sessionId = (char*)malloc(50);
    sprintf(sessionId, "session%lu", (unsigned long)hash(userId));

    strcpy(manager->sessions[manager->count].sessionId, sessionId);
    strcpy(manager->sessions[manager->count].userId, userId);
    manager->count++;

    return sessionId;
}

char* getUserId(Task53* manager, const char* sessionId) {
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            return manager->sessions[i].userId;
        }
    }
    return NULL;
}

void endSession(Task53* manager, const char* sessionId) {
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            for (int j = i; j < manager->count - 1; j++) {
                manager->sessions[j] = manager->sessions[j + 1];
            }
            manager->count--;
            break;
        }
    }
}

unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash;
}

int main() {
    Task53 manager;
    init(&manager);
    char* session1 = createSession(&manager, "user1");
    char* session2 = createSession(&manager, "user2");
    char* session3 = createSession(&manager, "user3");
    char* session4 = createSession(&manager, "user4");
    char* session5 = createSession(&manager, "user5");

    printf("%s\n", getUserId(&manager, session1)); // user1
    printf("%s\n", getUserId(&manager, session2)); // user2
    printf("%s\n", getUserId(&manager, session3)); // user3
    printf("%s\n", getUserId(&manager, session4)); // user4
    printf("%s\n", getUserId(&manager, session5)); // user5

    endSession(&manager, session3);

    printf("%s\n", getUserId(&manager, session3)); // (null)

    free(session1);
    free(session2);
    free(session3);
    free(session4);
    free(session5);

    return 0;
}