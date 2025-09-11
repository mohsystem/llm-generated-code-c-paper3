
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SESSION_TIMEOUT_SECONDS 1800 // 30 minutes
#define SESSION_ID_LENGTH 32
#define MAX_SESSIONS 1000
#define MAX_USER_ID_LENGTH 100

typedef struct {
    char userId[MAX_USER_ID_LENGTH];
    char sessionId[SESSION_ID_LENGTH + 1];
    time_t creationTime;
    time_t lastAccessTime;
    bool isActive;
} UserSession;

typedef struct {
    UserSession sessions[MAX_SESSIONS];
    int sessionCount;
} Task123;

// Function prototypes
void initializeSessionManager(Task123* manager);
char* createSession(Task123* manager, const char* userId);
bool validateSession(Task123* manager, const char* sessionId);
void invalidateSession(Task123* manager, const char* sessionId);
static void generateSecureSessionId(char* sessionId);
static bool isSessionExpired(const UserSession* session);
static void removeExistingUserSessions(Task123* manager, const char* userId);

void initializeSessionManager(Task123* manager) {
    manager->sessionCount = 0;
    for (int i = 0; i < MAX_SESSIONS; i++) {
        manager->sessions[i].isActive = false;
    }
    srand(time(NULL));
}

char* createSession(Task123* manager, const char* userId) {
    if (userId == NULL || strlen(userId) == 0 || strlen(userId) >= MAX_USER_ID_LENGTH) {
        return NULL;
    }

    // Remove existing sessions for this user
    removeExistingUserSessions(manager, userId);

    // Check if we have room for new session
    if (manager->sessionCount >= MAX_SESSIONS) {
        return NULL;
    }

    // Find empty slot
    int slot = -1;
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (!manager->sessions[i].isActive) {
            slot = i;
            break;
        }
    }

    if (slot == -1) return NULL;

    // Create new session
    UserSession* session = &manager->sessions[slot];
    strncpy(session->userId, userId, MAX_USER_', type='text')