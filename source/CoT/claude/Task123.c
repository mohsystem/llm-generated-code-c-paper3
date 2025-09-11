
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SESSIONS 100
#define SESSION_TOKEN_LENGTH 32
#define USER_ID_LENGTH 64
#define SESSION_TIMEOUT_SECONDS 1800 // 30 minutes

typedef struct {
    char userId[USER_ID_LENGTH];
    char sessionToken[SESSION_TOKEN_LENGTH * 2 + 1]; // Hex string representation
    time_t lastAccessTime;
    bool isActive;
} UserSession;

typedef struct {
    UserSession sessions[MAX_SESSIONS];
    int sessionCount;
} SessionManager;

void initSessionManager(SessionManager* manager) {
    manager->sessionCount = 0;
    for(int i = 0; i < MAX_SESSIONS; i++) {
        manager->sessions[i].isActive = false;
    }
}

char* generateSecureToken() {
    static char token[SESSION_TOKEN_LENGTH * 2 + 1];
    FILE* urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        return NULL;
    }
    
    unsigned char random_bytes[SESSION_TOKEN_LENGTH];
    fread(random_bytes, 1, SESSION_TOKEN_LENGTH, urandom);
    fclose(urandom);
    
    for(int i = 0; i < SESSION_TOKEN_LENGTH; i++) {
        sprintf(token + (i * 2), "%02x", random_bytes[i]);
    }
    return token;
}

char* createSession(SessionManager* manager, const char* userId) {
    if(userId == NULL || strlen(userId) == 0 || manager->sessionCount >= MAX_SESSIONS) {
        return NULL;
    }
    
    char* sessionToken = generateSecureToken();
    if(sessionToken == NULL) {
        return NULL;
    }
    
    UserSession* session = &manager->sessions[manager->sessionCount];
    strncpy(session->userId, userId, USER_ID_LENGTH - 1);
    session->userId[USER_ID_LENGTH - 1] = '\\0';
    strcpy(session->sessionToken, sessionToken);
    session->lastAccessTime = time(NULL);
    session->isActive = true;
    
    manager->sessionCount++;
    return session->sessionToken;
}

bool validateSession(SessionManager* manager, const char* sessionToken) {
    if(sessionToken == NULL) {
        return false;
    }
    
    time_t currentTime = time(NULL);
    
    for(int i = 0; i < manager->sessionCount; i++) {
        UserSession* session = &manager->sessions[i];
        if(session->isActive && strcmp(session->sessionToken, sessionToken) == 0) {
            if(currentTime - session->lastAccessTime > SESSION_TIMEOUT_SECONDS) {
                session->isActive = false;
                return false;
            }
            session->lastAccessTime = currentTime;
            return true;
        }
    }
    return false;
}

void invalidateSession(SessionManager* manager, const char* sessionToken) {
    if(sessionToken == NULL) {
        return;
    }
    
    for(int i = 0; i < manager->sessionCount; i++) {
        if(strcmp(manager->sessions[i].sessionToken, sessionToken) == 0) {
            manager->sessions[i].isActive = false;
            break;
        }
    }
}

int main() {
    SessionManager manager;
    initSessionManager(&manager);
    
    // Test Case 1: Create and validate session
    char* sessionToken1 = createSession(&manager, "user123");
    printf("Test 1: %s\\n", validateSession(&manager, sessionToken1) ? "true" : "false");
    
    // Test Case 2: Invalid session token
    printf("Test 2: %s\\n", validateSession(&manager, "invalid_token") ? "true" : "false");
    
    // Test Case 3: Invalidate session
    invalidateSession(&manager, sessionToken1);
    printf("Test 3: %s\\n", validateSession(&manager, sessionToken1) ? "true" : "false");
    
    // Test Case 4: Multiple sessions
    char* sessionToken2 = createSession(&manager, "user456");
    char* sessionToken3 = createSession(&manager, "user789");
    printf("Test 4: %s\\n", (validateSession(&manager, sessionToken2) && 
                           validateSession(&manager, sessionToken3)) ? "true" : "false");
    
    // Test Case 5: Null input handling
    printf("Test 5: %s\\n", createSession(&manager, "") == NULL ? 
           "Passed - Caught empty input" : "Failed");
    
    return 0;
}
