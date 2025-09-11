// Note: This is a simplified version without UUID generation and dynamic memory allocation
#include <stdio.h>
#include <stdbool.h>

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 37

char sessions[MAX_SESSIONS][SESSION_ID_LENGTH];
int sessionCount = 0;

bool isSessionValid(const char *sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i], sessionId) == 0) {
            return true;
        }
    }
    return false;
}

void endSession(const char *sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i], sessionId) == 0) {
            for (int j = i; j < sessionCount - 1; j++) {
                strcpy(sessions[j], sessions[j + 1]);
            }
            sessionCount--;
            break;
        }
    }
}

int main() {
    strcpy(sessions[sessionCount++], "sessionId1");
    strcpy(sessions[sessionCount++], "sessionId2");

    printf("%d\n", isSessionValid("sessionId1"));  // 1 (true)
    printf("%d\n", isSessionValid("sessionId2"));  // 1 (true)
    printf("%d\n", isSessionValid("invalidSessionId"));  // 0 (false)

    endSession("sessionId1");

    printf("%d\n", isSessionValid("sessionId1"));  // 0 (false)
    printf("%d\n", isSessionValid("sessionId2"));  // 1 (true)

    return 0;
}