
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 33
#define MAX_ATTRIBUTE_LENGTH 256
#define SESSION_TIMEOUT_SECONDS 1800 // 30 minutes

typedef struct {
    char key[MAX_ATTRIBUTE_LENGTH];
    char value[MAX_ATTRIBUTE_LENGTH];
} Attribute;

typedef struct {
    char sessionId[SESSION_ID_LENGTH];
    char userId[MAX_ATTRIBUTE_LENGTH];
    time_t lastAccessTime;
    Attribute attributes[10];
    int attributeCount;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int sessionCount;
} Task53;

void generateSessionId(char* sessionId) {
    const char charset[] = "0123456789abcdef";
    int i;
    for(i = 0; i < SESSION_ID_LENGTH - 1; i++) {
        sessionId[i] = charset[rand() % 16];
    }
    sessionId[SESSION_ID_LENGTH - 1] = '\\0';
}

int createSession(Task53* manager, const char* userId) {
    if(!userId || strlen(userId) == 0) {
        return -1;
    }
    
    if(manager->sessionCount >= MAX_SESSIONS) {
        return -1;
    }
    
    Session* newSession = &manager->sessions[manager->sessionCount];
    generateSessionId(newSession->sessionId);
    strncpy(newSession->userId, userId, MAX_ATTRIBUTE_LENGTH - 1);
    newSession->lastAccessTime = time(NULL);
    newSession->attributeCount = 0;
    
    manager->sessionCount++;
    return manager->sessionCount - 1;
}

int findSession(Task53* manager, const char* sessionId) {
    int i;
    for(i = 0; i < manager->sessionCount; i++) {
        if(strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            return i;
        }
    }
    return -1;
}

int validateSession(Task53* manager, const char* sessionId) {
    int index = findSession(manager, sessionId);
    if(index == -1) {
        return 0;
    }
    
    Session* session = &manager->sessions[index];
    time_t now = time(NULL);
    
    if(now - session->lastAccessTime > SESSION_TIMEOUT_SECONDS) {
        // Remove session by moving last session to this position
        if(index < manager->sessionCount - 1) {
            manager->sessions[index] = manager->sessions[manager->sessionCount - 1];
        }
        manager->sessionCount--;
        return 0;
    }
    
    session->lastAccessTime = now;
    return 1;
}

void invalidateSession(Task53* manager, const char* sessionId) {
    int index = findSession(manager, sessionId);
    if(index != -1) {
        if(index < manager->sessionCount - 1) {
            manager->sessions[index] = manager->sessions[manager->sessionCount - 1];
        }
        manager->sessionCount--;
    }
}

void setAttribute(Task53* manager, const char* sessionId, const char* key, const char* value) {
    int index = findSession(manager, sessionId);
    if(index != -1 && validateSession(manager, sessionId)) {
        Session* session = &manager->sessions[index];
        if(session->attributeCount < 10) {
            strncpy(session->attributes[session->attributeCount].key, key, MAX_ATTRIBUTE_LENGTH - 1);
            strncpy(session->attributes[session->attributeCount].value, value, MAX_ATTRIBUTE_LENGTH - 1);
            session->attributeCount++;
        }
    }
}

const char* getAttribute(Task53* manager, const char* sessionId, const char* key) {
    int index = findSession(manager, sessionId);
    if(index != -1 && validateSession(manager, sessionId)) {
        Session* session = &manager->sessions[index];
        int i;
        for(i = 0; i < session->attributeCount; i++) {
            if(strcmp(session->attributes[i].key, key) == 0) {
                return session->attributes[i].value;
            }
        }
    }
    return NULL;
}

int main() {
    Task53 manager = {0};
    srand(time(NULL));
    
    // Test Case 1: Create and validate session
    int sessionIndex = createSession(&manager, "user123");
    printf("Session created: %s\\n", manager.sessions[sessionIndex].sessionId);
    printf("Session valid: %d\\n", validateSession(&manager, manager.sessions[sessionIndex].sessionId));
    ', type='text')