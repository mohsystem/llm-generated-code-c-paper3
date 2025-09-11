#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sessionId[50];
    char token[50];
} CsrfToken;

CsrfToken csrfTokens[100];
int tokenCount = 0;

char* generateCsrfToken(const char* sessionId) {
    char* token = (char*)malloc(50);
    snprintf(token, 50, "%x%x%x%x", rand(), rand(), rand(), rand());
    strcpy(csrfTokens[tokenCount].sessionId, sessionId);
    strcpy(csrfTokens[tokenCount].token, token);
    tokenCount++;
    return token;
}

int verifyCsrfToken(const char* sessionId, const char* token) {
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(csrfTokens[i].sessionId, sessionId) == 0 &&
            strcmp(csrfTokens[i].token, token) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    const char* sessionId1 = "session1";
    const char* sessionId2 = "session2";
    const char* sessionId3 = "session3";
    const char* sessionId4 = "session4";
    const char* sessionId5 = "session5";

    char* token1 = generateCsrfToken(sessionId1);
    char* token2 = generateCsrfToken(sessionId2);
    char* token3 = generateCsrfToken(sessionId3);
    char* token4 = generateCsrfToken(sessionId4);
    char* token5 = generateCsrfToken(sessionId5);

    printf("%d\n", verifyCsrfToken(sessionId1, token1)); // 1
    printf("%d\n", verifyCsrfToken(sessionId2, token2)); // 1
    printf("%d\n", verifyCsrfToken(sessionId3, token3)); // 1
    printf("%d\n", verifyCsrfToken(sessionId4, "fake_token")); // 0
    printf("%d\n", verifyCsrfToken("invalid_session", token5)); // 0

    free(token1);
    free(token2);
    free(token3);
    free(token4);
    free(token5);

    return 0;
}