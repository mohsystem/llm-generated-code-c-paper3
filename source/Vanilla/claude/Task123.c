
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 33
#define USER_ID_LENGTH 21
#define SESSION_TIMEOUT 1800 // 30 minutes in seconds

typedef struct {
    char userId[USER_ID_LENGTH];
    char sessionId[SESSION_ID_LENGTH];
    time_t creationTime;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int sessionCount;
} Task123;

void initSessionManager(Task123* manager) {
    manager->sessionCount = 0;
}

void generateSessionId(char* sessionId) {
    const char charset[] = "0123456789abcdef";
    int i;
    for (i = 0; i < SESSION_ID_LENGTH - 1; i++) {
        sessionId[i] = charset[rand() % 16];
    }
    sessionId[SESSION_ID_LENGTH - 1] = '\\0';
}

char* createSession(Task123* manager, const char* userId) {
    if (manager->sessionCount >= MAX_SESSIONS) {
        return NULL;
    }

    Session* newSession = &manager->sessions[manager->sessionCount];
    strncpy(newSession->userId, userId, USER_ID_LENGTH - 1);
    newSession->userId[USER_ID_LENGTH - 1] = '\\0';
    
    generateSessionId(newSession->sessionId);
    newSession->creationTime = time(NULL);
    
    manager->sessionCount++;
    return newSession->sessionId;
}

int validateSession(Task123* manager, const char* sessionId) {
    time_t currentTime = time(NULL);
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            return (currentTime - manager->sessions[i].creationTime) <= SESSION_TIMEOUT;
        }
    }
    return 0;
}

void endSession(Task123* manager, const char* sessionId) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            if (i < manager->sessionCount - 1) {
                manager->sessions[i] = manager->sessions[manager->sessionCount - 1];
            }
            manager->sessionCount--;
            return;
        }
    }
}

int main() {
    Task123 sessionManager;
    initSessionManager(&sessionManager);
    srand(time(NULL));

    // Test Case 1: Create new session
    char* sessionId1 = createSession(&sessionManager, "user1");
    printf("Test 1 - Session Created: %s\\n", sessionId1);

    // Test Case 2: Validate valid session
    int isValid1 = validateSession(&sessionManager, sessionId1);
    printf("Test 2 - Session Valid: %d\\n", isValid1);

    // Test Case 3: End session
    endSession(&sessionManager, sessionId1);
    int isValid2 = validateSession(&sessionManager, sessionId1);
    printf("Test 3 - Session Valid After End: %d\\n", isValid2);

    // Test Case 4: Validate invalid session
    int isValid3 = validateSession(&sessionManager, "invalid-session");
    printf("Test 4 - Invalid Session Valid: %d\\n", isValid3);

    // Test Case 5: Create multiple sessions
    char* sessionId2 = createSession(&sessionManager, "user2");
    char* sessionId3 = createSession(&sessionManager, "user3");
    printf("Test 5 - Multiple Sessions Created: %d, %d\\n",
           validateSession(&sessionManager, sessionId2),
           validateSession(&sessionManager, sessionId3));

    return 0;
}
