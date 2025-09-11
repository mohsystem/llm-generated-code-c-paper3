#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100

typedef struct {
    char userId[50];
    long createdAt;
} Session;

Session sessions[MAX_USERS];
int sessionCount = 0;

void createSession(const char* userId) {
    if (sessionCount < MAX_USERS) {
        strcpy(sessions[sessionCount].userId, userId);
        sessions[sessionCount].createdAt = time(NULL);
        sessionCount++;
    }
}

Session* getSession(const char* userId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].userId, userId) == 0) {
            return &sessions[i];
        }
    }
    return NULL;
}

void endSession(const char* userId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].userId, userId) == 0) {
            for (int j = i; j < sessionCount - 1; j++) {
                sessions[j] = sessions[j + 1];
            }
            sessionCount--;
            break;
        }
    }
}

int main() {
    createSession("user1");
    createSession("user2");
    Session* s1 = getSession("user1");
    Session* s2 = getSession("user2");
    if (s1 != NULL) {
        printf("Session{userId=%s, createdAt=%ld}\n", s1->userId, s1->createdAt);
    }
    if (s2 != NULL) {
        printf("Session{userId=%s, createdAt=%ld}\n", s2->userId, s2->createdAt);
    }
    endSession("user1");
    Session* s3 = getSession("user1");
    if (s3 != NULL) {
        printf("Session{userId=%s, createdAt=%ld}\n", s3->userId, s3->createdAt);
    } else {
        printf("Session not found\n");
    }
    return 0;
}