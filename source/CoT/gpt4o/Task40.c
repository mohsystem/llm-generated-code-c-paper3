#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char sessionId[50];
    char csrfToken[50];
} Session;

Session sessions[100];
int sessionCount = 0;

char* generateCSRFToken() {
    static char token[33];
    const char *chars = "0123456789abcdef";
    for (int i = 0; i < 32; ++i) {
        token[i] = chars[rand() % 16];
    }
    token[32] = '\0';
    return token;
}

char* loginUser(const char *sessionId) {
    char *csrfToken = generateCSRFToken();
    strcpy(sessions[sessionCount].sessionId, sessionId);
    strcpy(sessions[sessionCount].csrfToken, csrfToken);
    sessionCount++;
    return csrfToken;
}

char* updateUserSettings(const char *sessionId, const char *csrfToken, const char *newSetting) {
    for (int i = 0; i < sessionCount; ++i) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0 && strcmp(sessions[i].csrfToken, csrfToken) == 0) {
            return "Settings updated successfully!";
        }
    }
    return "CSRF token validation failed!";
}

int main() {
    srand(time(NULL));

    // Simulating user login
    char sessionId[] = "session123";
    char *csrfToken = loginUser(sessionId);

    // Test cases
    printf("%s\n", updateUserSettings(sessionId, csrfToken, "newSetting1")); // Should succeed
    printf("%s\n", updateUserSettings(sessionId, "wrongToken", "newSetting2")); // Should fail
    printf("%s\n", updateUserSettings("wrongSession", csrfToken, "newSetting3")); // Should fail
    printf("%s\n", updateUserSettings(sessionId, csrfToken, "newSetting4")); // Should succeed
    printf("%s\n", updateUserSettings("anotherSession", "anotherToken", "newSetting5")); // Should fail

    return 0;
}