#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>

typedef struct Session {
    char username[256];
    time_t expirationTime;
    char data[256];
} Session;

typedef struct SessionManager {
    Session* sessions;
    int sessionCount;
} SessionManager;

SessionManager* createSessionManager() {
    SessionManager* manager = malloc(sizeof(SessionManager));
    manager->sessions = NULL;
    manager->sessionCount = 0;
    return manager;
}

void freeSessionManager(SessionManager* manager) {
    free(manager->sessions);
    free(manager);
}

char* generateUUID() {
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    char uuid[37];
    uuid_unparse(bin_uuid, uuid);
    return strdup(uuid);
}

void createSession(SessionManager* manager, const char* username) {
    manager->sessionCount++;
    manager->sessions = realloc(manager->sessions, sizeof(Session) * manager->sessionCount);

    Session* session = &manager->sessions[manager->sessionCount - 1];
    strcpy(session->username, username);
    session->expirationTime = time(NULL) + 15 * 60; // 15 minutes
    strcpy(session->data, "");
}

void updateSession(SessionManager* manager, const char* sessionId, const char* key, const char* value) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].username, sessionId) == 0) {
            sprintf(manager->sessions[i].data, "%s: %s", key, value);
            return;
        }
    }
}

char* getSessionData(SessionManager* manager, const char* sessionId) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].username, sessionId) == 0 && time(NULL) < manager->sessions[i].expirationTime) {
            return strdup(manager->sessions[i].data);
        }
    }
    return strdup("Session expired or does not exist");
}

void expireSession(SessionManager* manager, const char* sessionId) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].username, sessionId) == 0) {
            // For simplicity, we just mark the session as expired by setting the expiration time to the past.
            manager->sessions[i].expirationTime = 0;
            return;
        }
    }
}

int main() {
    SessionManager* sessionManager = createSessionManager();
    char* sessionId1 = generateUUID();
    createSession(sessionManager, sessionId1);

    char* sessionId2 = generateUUID();
    createSession(sessionManager, sessionId2);

    updateSession(sessionManager, sessionId1, "key", "value");
    printf("%s\n", getSessionData(sessionManager, sessionId1));

    expireSession(sessionManager, sessionId2);
    printf("%s\n", getSessionData(sessionManager, sessionId2));

    freeSessionManager(sessionManager);
    free(sessionId1);
    free(sessionId2);

    return 0;
}