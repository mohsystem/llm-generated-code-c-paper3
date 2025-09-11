#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char sessionId[37];
    char userId[50];
} Session;

Session sessionStore[100];
int sessionCount = 0;

void generateUUID(char* uuid) {
    snprintf(uuid, 37, "%04x%04x-%04x-%04x-%04x-%04x%04x%04x",
             rand() % 0x10000, rand() % 0x10000, rand() % 0x10000,
             rand() % 0x10000, rand() % 0x10000, rand() % 0x10000,
             rand() % 0x10000, rand() % 0x10000);
}

void createSession(const char* userId, char* sessionId) {
    generateUUID(sessionId);
    strcpy(sessionStore[sessionCount].sessionId, sessionId);
    strcpy(sessionStore[sessionCount].userId, userId);
    sessionCount++;
}

const char* getUserId(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessionStore[i].sessionId, sessionId) == 0) {
            return sessionStore[i].userId;
        }
    }
    return NULL;
}

void endSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessionStore[i].sessionId, sessionId) == 0) {
            for (int j = i; j < sessionCount - 1; j++) {
                sessionStore[j] = sessionStore[j + 1];
            }
            sessionCount--;
            break;
        }
    }
}

int isValidSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessionStore[i].sessionId, sessionId) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    // Test cases
    char sessionId1[37];
    createSession("user1", sessionId1);
    printf("%s\n", getUserId(sessionId1));
    printf("%d\n", isValidSession(sessionId1));
    endSession(sessionId1);
    printf("%d\n", isValidSession(sessionId1));

    char sessionId2[37];
    createSession("user2", sessionId2);
    printf("%s\n", getUserId(sessionId2));
    endSession(sessionId2);

    return 0;
}