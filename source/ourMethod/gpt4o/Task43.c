#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 33

typedef struct {
    char sessionId[SESSION_ID_LENGTH];
    char userId[50];
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int sessionCount;
} Task43;

void initSessionManager(Task43 *manager) {
    manager->sessionCount = 0;
    srand(time(NULL));
}

void generateSessionId(char *sessionId) {
    static const char hex_chars[] = "0123456789ABCDEF";
    for (int i = 0; i < SESSION_ID_LENGTH - 1; ++i) {
        sessionId[i] = hex_chars[rand() % 16];
    }
    sessionId[SESSION_ID_LENGTH - 1] = '\0';
}

char* createSession(Task43 *manager, const char *userId) {
    if (manager->sessionCount >= MAX_SESSIONS) return NULL;

    char sessionId[SESSION_ID_LENGTH];
    generateSessionId(sessionId);

    strcpy(manager->sessions[manager->sessionCount].sessionId, sessionId);
    strcpy(manager->sessions[manager->sessionCount].userId, userId);
    manager->sessionCount++;

    return manager->sessions[manager->sessionCount - 1].sessionId;
}

char* getUserId(Task43 *manager, const char *sessionId) {
    for (int i = 0; i < manager->sessionCount; ++i) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            return manager->sessions[i].userId;
        }
    }
    return NULL;
}

void terminateSession(Task43 *manager, const char *sessionId) {
    for (int i = 0; i < manager->sessionCount; ++i) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            manager->sessions[i] = manager->sessions[manager->sessionCount - 1];
            manager->sessionCount--;
            return;
        }
    }
}

int main() {
    Task43 sessionManager;
    initSessionManager(&sessionManager);

    char *session1 = createSession(&sessionManager, "user1");
    char *session2 = createSession(&sessionManager, "user2");
    char *session3 = createSession(&sessionManager, "user3");
    char *session4 = createSession(&sessionManager, "user4");
    char *session5 = createSession(&sessionManager, "user5");

    printf("Session1 userId: %s\n", getUserId(&sessionManager, session1));
    printf("Session2 userId: %s\n", getUserId(&sessionManager, session2));
    printf("Session3 userId: %s\n", getUserId(&sessionManager, session3));

    terminateSession(&sessionManager, session1);
    printf("Session1 userId after termination: %s\n", getUserId(&sessionManager, session1));

    terminateSession(&sessionManager, session2);
    printf("Session2 userId after termination: %s\n", getUserId(&sessionManager, session2));

    return 0;
}