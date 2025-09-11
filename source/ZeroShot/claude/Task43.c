
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SESSION_ID_LENGTH 32
#define SESSION_TIMEOUT_SECONDS 1800
#define MAX_SESSIONS 100
#define USER_ID_LENGTH 32

typedef struct {
    char sessionId[SESSION_ID_LENGTH + 1];
    char userId[USER_ID_LENGTH + 1];
    time_t createdAt;
    time_t lastAccessed;
    bool isActive;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int sessionCount;
} SessionManager;

void initSessionManager(SessionManager* manager) {
    manager->sessionCount = 0;
    memset(manager->sessions, 0, sizeof(manager->sessions));
}

void generateRandomString(char* str, size_t length) {
    static const char charset[] = "0123456789abcdef";
    for (size_t i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[length] = '\\0';
}

char* createSession(SessionManager* manager, const char* userId) {
    if (manager->sessionCount >= MAX_SESSIONS) {
        return NULL;
    }
    
    if (!userId || strlen(userId) == 0 || strlen(userId) >= USER_ID_LENGTH) {
        return NULL;
    }
    
    Session* newSession = &manager->sessions[manager->sessionCount];
    generateRandomString(newSession->sessionId, SESSION_ID_LENGTH);
    strncpy(newSession->userId, userId, USER_ID_LENGTH);
    newSession->createdAt = time(NULL);
    newSession->lastAccessed = time(NULL);
    newSession->isActive = true;
    
    manager->sessionCount++;
    return newSession->sessionId;
}

bool validateSession(SessionManager* manager, const char* sessionId) {
    if (!sessionId) {
        return false;
    }
    
    for (int i = 0; i < manager->sessionCount; i++) {
        Session* session = &manager->sessions[i];
        if (session->isActive && strcmp(session->sessionId, sessionId) == 0) {
            time_t now = time(NULL);
            if (now - session->lastAccessed > SESSION_TIMEOUT_SECONDS) {
                session->isActive = false;
                return false;
            }
            session->lastAccessed = now;
            return true;
        }
    }
    return false;
}

void terminateSession(SessionManager* manager, const char* sessionId) {
    if (!sessionId) {
        return;
    }
    
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            manager->sessions[i].isActive = false;
            break;
        }
    }
}

int main() {
    SessionManager manager;
    initSessionManager(&manager);
    srand(time(NULL));
    
    // Test Case 1: Create new session
    char* sessionId1 = createSession(&manager, "user123");
    printf("Test 1 - New Session Created: %s\\n", sessionId1 ? sessionId1 : "NULL");
    
    // Test Case 2: Validate valid session
    bool isValid = validateSession(&manager, sessionId1);
    printf("Test 2 - Session Valid: %s\\n", isValid ? "true" : "false");
    
    // Test Case 3: Validate invalid session
    bool invalidSession = validateSession(&manager, "invalid_session_id");
    printf("Test 3 - Invalid Session: %s\\n", invalidSession ? "true" : "false");
    
    // Test Case 4: Terminate session
    terminateSession(&manager, sessionId1);
    bool terminatedSession = validateSession(&manager, sessionId1);
    printf("Test 4 - Terminated Session Valid: %s\\n", terminatedSession ? "true" : "false");
    
    // Test Case 5: Create and validate multiple sessions
    char* sessionId2 = createSession(&manager, "user456");
    char* sessionId3 = createSession(&manager, "user789");
    bool multipleValid = validateSession(&manager, sessionId2) && 
                        validateSession(&manager, sessionId3);
    printf("Test 5 - Multiple Sessions Valid: %s\\n", multipleValid ? "true" : "false");
    
    return 0;
}
