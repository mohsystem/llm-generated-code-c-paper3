
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 33
#define USER_ID_LENGTH 50
#define SESSION_TIMEOUT_MINS 30

typedef struct {
    char sessionId[SESSION_ID_LENGTH];
    char userId[USER_ID_LENGTH];
    time_t lastAccessTime;
    bool isValid;
} Session;

static Session sessions[MAX_SESSIONS];
static int sessionCount = 0;

void generateSessionId(char* sessionId) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i;
    for(i = 0; i < SESSION_ID_LENGTH - 1; i++) {
        int key = rand() % (sizeof(charset) - 1);
        sessionId[i] = charset[key];
    }
    sessionId[SESSION_ID_LENGTH - 1] = '\\0';
}

char* createSession(const char* userId) {
    if(userId == NULL || strlen(userId) == 0 || sessionCount >= MAX_SESSIONS) {
        return NULL;
    }
    
    Session* session = &sessions[sessionCount++];
    strncpy(session->userId, userId, USER_ID_LENGTH - 1);
    session->userId[USER_ID_LENGTH - 1] = '\\0';
    generateSessionId(session->sessionId);
    session->lastAccessTime = time(NULL);
    session->isValid = true;
    
    return session->sessionId;
}

bool validateSession(const char* sessionId) {
    if(sessionId == NULL) {
        return false;
    }
    
    int i;
    for(i = 0; i < sessionCount; i++) {
        if(strcmp(sessions[i].sessionId, sessionId) == 0) {
            if(!sessions[i].isValid) {
                return false;
            }
            
            time_t now = time(NULL);
            if(now - sessions[i].lastAccessTime > SESSION_TIMEOUT_MINS * 60) {
                sessions[i].isValid = false;
                return false;
            }
            
            sessions[i].lastAccessTime = now;
            return true;
        }
    }
    return false;
}

void invalidateSession(const char* sessionId) {
    if(sessionId == NULL) {
        return;
    }
    
    int i;
    for(i = 0; i < sessionCount; i++) {
        if(strcmp(sessions[i].sessionId, sessionId) == 0) {
            sessions[i].isValid = false;
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    
    // Test Case 1: Create valid session
    char* sessionId1 = createSession("user123");
    printf("Test 1: %s\\n", (sessionId1 != NULL && validateSession(sessionId1)) ? "true" : "false");
    
    // Test Case 2: Invalid session id
    printf("Test 2: %s\\n", (!validateSession("invalid_session")) ? "true" : "false");
    
    // Test Case 3: NULL session id
    printf("Test 3: %s\\n", (!validateSession(NULL)) ? "true" : "false");
    
    // Test Case 4: Invalidate session
    char* sessionId2 = createSession("user456");
    invalidateSession(sessionId2);
    printf("Test 4: %s\\n", (!validateSession(sessionId2)) ? "true" : "false");
    
    // Test Case 5: Empty user id
    printf("Test 5: %s\\n", (createSession("") == NULL) ? "true" : "false");
    
    return 0;
}
