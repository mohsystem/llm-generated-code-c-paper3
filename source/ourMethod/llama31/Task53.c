#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <uuid/uuid.h>

typedef struct Session {
    char username[100];
    char sessionId[37];
    time_t expirationTime;
} Session;

typedef struct SessionMap {
    char sessionId[37];
    Session session;
} SessionMap;

SessionMap* sessions = NULL;
int sessionCount = 0;

void createSession(const char* username, char* sessionId, time_t* expirationTime) {
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    uuid_unparse(bin_uuid, sessionId);
    *expirationTime = time(NULL) + 30 * 60; // 30 minutes

    if (sessions == NULL) {
        sessions = malloc(sizeof(SessionMap));
        sessionCount = 1;
    } else {
        sessions = realloc(sessions, (sessionCount + 1) * sizeof(SessionMap));
        sessionCount++;
    }

    strcpy(sessions[sessionCount - 1].sessionId, sessionId);
    strcpy(sessions[sessionCount - 1].session.username, username);
    sessions[sessionCount - 1].session.expirationTime = *expirationTime;
}

void validateSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0 && difftime(time(NULL), sessions[i].session.expirationTime) < 0) {
            printf("Session is valid for user: %s\n", sessions[i].session.username);
            return;
        }
    }
    printf("Invalid or expired session\n");
}

void terminateSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            // Shift elements to fill the gap
            for (int j = i; j < sessionCount - 1; j++) {
                sessions[j] = sessions[j + 1];
            }
            sessionCount--;
            sessions = realloc(sessions, sessionCount * sizeof(SessionMap));
            return;
        }
    }
}

int main() {
    char sessionId[37];
    time_t expirationTime;
    createSession("user123", sessionId, &expirationTime);
    validateSession(sessionId);
    terminateSession(sessionId);
    free(sessions);
    return 0;
}