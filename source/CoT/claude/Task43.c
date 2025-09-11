
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SESSION_ID_LENGTH 32
#define SESSION_TIMEOUT_MINUTES 30
#define MAX_SESSIONS 100
#define MAX_USER_ID_LENGTH 64

typedef struct {
    char userId[MAX_USER_ID_LENGTH];
    time_t createdAt;
    time_t lastAccessedAt;
    char sessionId[SESSION_ID_LENGTH * 2 + 1];
    bool isActive;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int sessionCount;
} SessionManager;

void initSessionManager(SessionManager* manager) {
    manager->sessionCount = 0;
    for(int i = 0; i < MAX_SESSIONS; i++) {
        manager->sessions[i].isActive = false;
    }
}

void generateSecureSessionId(char* sessionId) {
    static const char hex_chars[] = "0123456789abcdef";
    for(int i = 0; i < SESSION_ID_LENGTH * 2; i++) {
        sessionId[i] = hex_chars[rand() % 16];
    }
    sessionId[SESSION_ID_LENGTH * 2] = '\\0';
}

const char* createSession(SessionManager* manager, const char* userId) {
    if(!userId || strlen(userId) == 0 || strlen(userId) >= MAX_USER_ID_LENGTH) {
        return NULL;
    }
    
    if(manager->sessionCount >= MAX_SESSIONS) {
        return NULL;
    }
    
    int index = -1;
    for(int i = 0; i < MAX_SESSIONS; i++) {
        if(!manager->sessions[i].isActive) {
            index = i;
            break;
        }
    }
    
    if(index == -1) return NULL;
    
    Session* session = &manager->sessions[index];
    strncpy(session->userId, userId, MAX_USER_ID_LENGTH - 1);
    session->userId[MAX_USER_ID_LENGTH - 1] = '\\0';
    session->createdAt = time(NULL);
    session->lastAccessedAt = time(NULL);
    generateSecureSessionId(session->sessionId);
    session->isActive = true;
    manager->sessionCount++;
    
    return session->sessionId;
}

bool validateSession(SessionManager* manager, const char* sessionId) {
    if(!sessionId) return false;
    
    for(int i = 0; i < MAX_SESSIONS; i++) {
        Session* session = &manager->sessions[i];
        if(session->isActive && strcmp(session->sessionId, sessionId) == 0) {
            time_t now = time(NULL);
            if(difftime(now, session->lastAccessedAt) >= SESSION_TIMEOUT_MINUTES * 60) {
                session->isActive = false;
                manager->sessionCount--;
                return false;
            }
            session->lastAccessedAt = now;
            return true;
        }
    }
    return false;
}

void terminateSession(SessionManager* manager, const char* sessionId) {
    if(!sessionId) return;
    
    for(int i = 0; i < MAX_SESSIONS; i++) {
        Session* session = &manager->sessions[i];
        if(session->isActive && strcmp(session->sessionId, sessionId) == 0) {
            session->isActive = false;
            manager->sessionCount--;
            return;
        }
    }
}

int main() {
    srand(time(NULL));
    SessionManager manager;
    initSessionManager(&manager);
    
    // Test Case 1: Create and validate session
    const char* sessionId1 = createSession(&manager, "user123");
    printf("Test 1 - Session valid: %d\\n", validateSession(&manager, sessionId1));
    
    // Test Case 2: Invalid session ID
    printf("Test 2 - Invalid session: %d\\n", validateSession(&manager, "invalid_session_id"));
    
    // Test Case 3: Terminate session
    terminateSession(&manager, sessionId1);
    printf("Test 3 - Terminated session valid: %d\\n", validateSession(&manager, sessionId1));
    
    // Test Case 4: Null user ID
    const char* nullSession = createSession(&manager, NULL);
    printf("Test 4 - Null user ID session: %s\\n", nullSession == NULL ? "Correctly rejected" : "Incorrectly accepted");
    
    // Test Case 5: Multiple sessions
    const char* sessionId2 = createSession(&manager, "user456");
    const char* sessionId3 = createSession(&manager, "user789");
    printf("Test 5 - Multiple sessions valid: %d\\n", 
           validateSession(&manager, sessionId2) && validateSession(&manager, sessionId3));
    
    return 0;
}
