// C code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TOKEN_LENGTH 33

typedef struct {
    char sessionId[50];
    char token[TOKEN_LENGTH];
} CsrfToken;

CsrfToken csrfTokens[10]; // Assuming max 10 sessions for simplicity
int csrfTokenCount = 0;

char* generateRandomToken() {
    static char hex_chars[] = "0123456789abcdef";
    static char token[TOKEN_LENGTH];
    for (int i = 0; i < TOKEN_LENGTH - 1; ++i) {
        token[i] = hex_chars[rand() % 16];
    }
    token[TOKEN_LENGTH - 1] = '\0';
    return token;
}

char* generateCsrfToken(char* sessionId) {
    char* token = generateRandomToken();
    strcpy(csrfTokens[csrfTokenCount].sessionId, sessionId);
    strcpy(csrfTokens[csrfTokenCount].token, token);
    csrfTokenCount++;
    return token;
}

int validateCsrfToken(char* sessionId, char* token) {
    for (int i = 0; i < csrfTokenCount; i++) {
        if (strcmp(csrfTokens[i].sessionId, sessionId) == 0 && strcmp(csrfTokens[i].token, token) == 0) {
            return 1;
        }
    }
    return 0;
}

char* updateUserSettings(char* sessionId, char* token, char* newSettings) {
    static char response[100];
    if (validateCsrfToken(sessionId, token)) {
        sprintf(response, "Settings updated to: %s", newSettings);
    } else {
        sprintf(response, "CSRF Token validation failed.");
    }
    return response;
}

int main() {
    srand(time(NULL)); // Initialize random seed
    char* sessionId = "session123";
    char* validToken = generateCsrfToken(sessionId);
    char* invalidToken = "invalidToken";

    printf("%s\n", updateUserSettings(sessionId, validToken, "New Settings 1")); // Should succeed
    printf("%s\n", updateUserSettings(sessionId, invalidToken, "New Settings 2")); // Should fail
    printf("%s\n", updateUserSettings("wrongSession", validToken, "New Settings 3")); // Should fail
    printf("%s\n", updateUserSettings(sessionId, "", "New Settings 4")); // Should fail
    printf("%s\n", updateUserSettings(sessionId, validToken, "New Settings 5")); // Should succeed

    return 0;
}