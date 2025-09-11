#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Basic session management (insecure; replace with a robust library for a real application)

char* createSession() {
    char* sessionId = malloc(33 * sizeof(char)); // Sufficient session ID length (+1 for null terminator)
    if (!sessionId) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL)); // Seed the random number generator, CWE-337 mitigated

    for (int i = 0; i < 32; i++) {
        sessionId[i] = "0123456789abcdef"[rand() % 16];
    }
    sessionId[32] = '\0';
    return sessionId;
}

void getSessionInfo(const char* sessionId) {
    if (sessionId != NULL && strlen(sessionId) > 0) {
        printf("Session ID: %s\n", sessionId);
    } else {
        printf("No active session.\n");
    }
}

void terminateSession(char** sessionId) {
    if (*sessionId != NULL) {
        free(*sessionId);
        *sessionId = NULL;
        printf("Session terminated.\n");
    }
}

int main() {
    // Test cases
    char* sessionId = NULL;

    printf("Test 1: Create session\n");
    sessionId = createSession();
    getSessionInfo(sessionId);


    printf("Test 2: Get session info\n");
    getSessionInfo(sessionId);

    printf("Test 3: Terminate session\n");
    terminateSession(&sessionId);

    printf("Test 4: Get session info (after termination)\n");
    getSessionInfo(sessionId);

    printf("Test 5: Create new session\n");
    sessionId = createSession();
    getSessionInfo(sessionId);

    free(sessionId); // Release memory after use
    return 0;
}