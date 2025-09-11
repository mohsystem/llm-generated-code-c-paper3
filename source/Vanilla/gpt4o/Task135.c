#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char sessionId[256];
    char csrfToken[256];
} SessionToken;

SessionToken sessionTokens[100];
int tokenCount = 0;

void generateRandomToken(char *token, size_t length) {
    static const char hexChars[] = "0123456789abcdef";
    for (size_t i = 0; i < length; i++) {
        token[i] = hexChars[rand() % 16];
    }
    token[length] = '\0';
}

void generateCSRFToken(const char *sessionId, char *outputToken) {
    generateRandomToken(outputToken, 32);
    strcpy(sessionTokens[tokenCount].sessionId, sessionId);
    strcpy(sessionTokens[tokenCount].csrfToken, outputToken);
    tokenCount++;
}

int validateCSRFToken(const char *sessionId, const char *csrfToken) {
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(sessionTokens[i].sessionId, sessionId) == 0 &&
            strcmp(sessionTokens[i].csrfToken, csrfToken) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));

    char session1[] = "session1";
    char session2[] = "session2";
    char session3[] = "session3";
    char session4[] = "session4";
    char session5[] = "session5";

    char token1[33];
    char token2[33];
    char token3[33];
    char token4[33];
    char token5[33];

    generateCSRFToken(session1, token1);
    generateCSRFToken(session2, token2);
    generateCSRFToken(session3, token3);
    generateCSRFToken(session4, token4);
    generateCSRFToken(session5, token5);

    printf("%d\n", validateCSRFToken(session1, token1)); // 1
    printf("%d\n", validateCSRFToken(session2, token2)); // 1
    printf("%d\n", validateCSRFToken(session3, "wrongtoken")); // 0
    printf("%d\n", validateCSRFToken(session4, token4)); // 1
    printf("%d\n", validateCSRFToken(session5, token1)); // 0

    return 0;
}