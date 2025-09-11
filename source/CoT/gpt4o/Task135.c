#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SESSIONS 100

typedef struct {
    char sessionId[50];
    char token[50];
} SessionToken;

SessionToken sessionTokens[MAX_SESSIONS];
int sessionCount = 0;

const char* generateToken(const char* sessionId) {
    static char token[50];
    snprintf(token, sizeof(token), "%d", rand());
    for (int i = 0; i < sessionCount; ++i) {
        if (strcmp(sessionTokens[i].sessionId, sessionId) == 0) {
            strcpy(sessionTokens[i].token, token);
            return token;
        }
    }
    if (sessionCount < MAX_SESSIONS) {
        strcpy(sessionTokens[sessionCount].sessionId, sessionId);
        strcpy(sessionTokens[sessionCount].token, token);
        sessionCount++;
    }
    return token;
}

int verifyToken(const char* sessionId, const char* token) {
    for (int i = 0; i < sessionCount; ++i) {
        if (strcmp(sessionTokens[i].sessionId, sessionId) == 0 &&
            strcmp(sessionTokens[i].token, token) == 0) {
            return 1;
        }
    }
    return 0;
}

// Test cases
int main() {
    srand(time(NULL));

    const char* sessionId1 = "session1";
    const char* sessionId2 = "session2";

    const char* token1 = generateToken(sessionId1);
    const char* token2 = generateToken(sessionId2);

    printf("%d\n", verifyToken(sessionId1, token1)); // Expected: 1
    printf("%d\n", verifyToken(sessionId1, "wrongToken")); // Expected: 0
    printf("%d\n", verifyToken(sessionId2, token2)); // Expected: 1
    printf("%d\n", verifyToken(sessionId2, token1)); // Expected: 0
    printf("%d\n", verifyToken("invalidSession", token1)); // Expected: 0

    return 0;
}