
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 32
#define MAX_DATA_ITEMS 50
#define SESSION_TIMEOUT 1800 // 30 minutes in seconds

typedef struct {
    char key[50];
    char value[100];
} SessionData;

typedef struct {
    char sessionId[SESSION_ID_LENGTH + 1];
    char userId[50];
    time_t lastAccessed;
    SessionData data[MAX_DATA_ITEMS];
    int dataCount;
    int isActive;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int sessionCount;
} Task53;

void initializeSessionManager(Task53* manager) {
    manager->sessionCount = 0;
}

char* generateSessionId() {
    static char sessionId[SESSION_ID_LENGTH + 1];
    const char charset[] = "0123456789abcdef";
    
    for (int i = 0; i < SESSION_ID_LENGTH; i++) {
        int index = rand() % 16;
        sessionId[i] = charset[index];
    }
    sessionId[SESSION_ID_LENGTH] = '\\0';
    return sessionId;
}

char* createSession(Task53* manager, const char* userId) {
    if (manager->sessionCount >= MAX_SESSIONS) return NULL;
    
    Session* newSession = &manager->sessions[manager->sessionCount];
    strcpy(newSession->sessionId, generateSessionId());
    strcpy(newSession->userId, userId);
    newSession->lastAccessed = time(NULL);
    newSession->dataCount = 0;
    newSession->isActive = 1;
    
    manager->sessionCount++;
    return newSession->sessionId;
}

int isValidSession(Task53* manager, const char* sessionId) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0 && 
            manager->sessions[i].isActive) {
            time_t now = time(NULL);
            if (now - manager->sessions[i].lastAccessed > SESSION_TIMEOUT) {
                manager->sessions[i].isActive = 0;
                return 0;
            }
            manager->sessions[i].lastAccessed = now;
            return 1;
        }
    }
    return 0;
}

void addSessionData(Task53* manager, const char* sessionId, const char* key, const char* value) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0 && 
            manager->sessions[i].isActive) {
            if (manager->sessions[i].dataCount < MAX_DATA_ITEMS) {
                SessionData* data = &manager->sessions[i].data[manager->sessions[i].dataCount];
                strcpy(data->key, key);
                strcpy(data->value, value);
                manager->sessions[i].dataCount++;
                manager->sessions[i].lastAccessed = time(NULL);
            }
            break;
        }
    }
}

char* getSessionData(Task53* manager, const char* sessionId, const char* key) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0 && 
            manager->sessions[i].isActive) {
            for (int j = 0; j < manager->sessions[i].dataCount; j++) {
                if (strcmp(manager->sessions[i].data[j].key, key) == 0) {
                    manager->sessions[i].lastAccessed = time(NULL);
                    return manager->sessions[i].data[j].value;
                }
            }
        }
    }
    return NULL;
}

void invalidateSession(Task53* manager, const char* sessionId) {
    for (int i = 0; i < manager->sessionCount; i++) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            manager->sessions[i].isActive = 0;
            break;
        }
    }
}

int main() {
    Task53 sessionManager;
    initializeSessionManager(&sessionManager);
    
    // Test case 1: Create new session
    char* sessionId1 = createSession(&sessionManager, "user1");
    printf("Test 1 - New session created: %s\\n", sessionId1);
    
    // Test case 2: Add and retrieve session data
    addSessionData(&sessionManager, sessionId1, "role", "admin");
    printf("Test 2 - Session data: %s\\n", getSessionData(&sessionManager, sessionId1, "role"));
    
    // Test case 3: Validate session
    printf("Test 3 - Session valid: %d\\n", isValidSession(&sessionManager, sessionId1));
    
    // Test case 4: Invalid session
    printf("Test 4 - Invalid session: %d\\n", isValidSession(&sessionManager, "invalid-session"));
    
    // Test case 5: Invalidate session
    invalidateSession(&sessionManager, sessionId1);
    printf("Test 5 - Session after invalidation: %d\\n", isValidSession(&sessionManager, sessionId1));
    
    return 0;
}
