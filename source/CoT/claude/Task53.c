
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SESSIONS 1000
#define SESSION_TIMEOUT 1800 // 30 minutes in seconds
#define SESSION_ID_LENGTH 37 // 36 chars + null terminator
#define USER_ID_LENGTH 64

typedef struct {
    char sessionId[SESSION_ID_LENGTH];
    char userId[USER_ID_LENGTH];
    time_t lastAccessTime;
    bool isValid;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int sessionCount;
} Task53;

void initSessionManager(Task53* manager) {
    manager->sessionCount = 0;
}

void generateSessionId(char* sessionId) {
    const char hex_chars[] = "0123456789abcdef";
    int pos = 0;
    
    for(int i = 0; i < 36; i++) {
        if(i == 8 || i == 13 || i == 18 || i == 23) {
            sessionId[pos++] = '-';
        } else {
            sessionId[pos++] = hex_chars[rand() % 16];
        }
    }
    sessionId[pos] = '\\0';
}

void cleanupExpiredSessions(Task53* manager) {
    time_t currentTime = time(NULL);
    int validCount = 0;
    
    for(int i = 0; i < manager->sessionCount; i++) {
        if(manager->sessions[i].isValid && 
           (currentTime - manager->sessions[i].lastAccessTime) <= SESSION_TIMEOUT) {
            if(i != validCount) {
                manager->sessions[validCount] = manager->sessions[i];
            }
            validCount++;
        }
    }
    manager->sessionCount = validCount;
}

bool createSession(Task53* manager, const char* userId, char* sessionId) {
    if(manager->sessionCount >= MAX_SESSIONS) {
        cleanupExpiredSessions(manager);
    }
    
    if(manager->sessionCount >= MAX_SESSIONS) {
        return false;
    }
    
    generateSessionId(sessionId);
    
    Session* newSession = &manager->sessions[manager->sessionCount++];
    strncpy(newSession->sessionId, sessionId, SESSION_ID_LENGTH - 1);
    strncpy(newSession->userId, userId, USER_ID_LENGTH - 1);
    newSession->lastAccessTime = time(NULL);
    newSession->isValid = true;
    
    return true;
}

bool validateSession(Task53* manager, const char* sessionId) {
    for(int i = 0; i < manager->sessionCount; i++) {
        if(strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            if(!manager->sessions[i].isValid) {
                return false;
            }
            
            time_t currentTime = time(NULL);
            if((currentTime - manager->sessions[i].lastAccessTime) > SESSION_TIMEOUT) {
                manager->sessions[i].isValid = false;
                return false;
            }
            
            manager->sessions[i].lastAccessTime = currentTime;
            return true;
        }
    }
    return false;
}

void invalidateSession(Task53* manager, const char* sessionId) {
    for(int i = 0; i < manager->sessionCount; i++) {
        if(strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            manager->sessions[i].isValid = false;
            break;
        }
    }
}
//
// int main() {
//     Task53 sessionManager;
//     initSessionManager(&sessionManager);
//     srand(time(NULL));
//
//     // Test', type='text')