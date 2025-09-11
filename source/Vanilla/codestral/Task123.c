// C does not have built-in support for dynamic data structures like maps or dictionaries,
// so a more complex solution would be required for a real-world application.
// This example uses a fixed-size array for simplicity.

#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

char sessions[MAX_USERS][2][10]; // [user][session or empty]

void startSession(const char* userId, const char* sessionId) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strlen(sessions[i][0]) == 0) {
            strcpy(sessions[i][0], userId);
            strcpy(sessions[i][1], sessionId);
            return;
        }
    }
}

void endSession(const char* userId) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(sessions[i][0], userId) == 0) {
            sessions[i][0][0] = '\0';
            sessions[i][1][0] = '\0';
            return;
        }
    }
}

int isSessionActive(const char* userId) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(sessions[i][0], userId) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    // Test cases
    startSession("user1", "session1");
    printf("%d\n", isSessionActive("user1")); // 1 (true)

    endSession("user1");
    printf("%d\n", isSessionActive("user1")); // 0 (false)

    return 0;
}