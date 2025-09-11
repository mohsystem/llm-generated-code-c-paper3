#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Session {
    char sessionId[37];
    char username[50];
} Session;

typedef struct SessionManager {
    Session *sessions;
    size_t sessionCount;
} SessionManager;

void initSessionManager(SessionManager *manager) {
    manager->sessions = NULL;
    manager->sessionCount = 0;
}

char *generateUUID() {
    static char uuid[37];
    const char *c = "89ab";
    sprintf(uuid, "%x%x-%x-%x-%c%x-%x%x%x",
            rand(), rand(), rand(),
            ((rand() & 0x0fff) | 0x4000),
            c[rand() % strlen(c)],
            rand(), rand(), rand(), rand());
    return uuid;
}

char *createSession(SessionManager *manager, const char *username) {
    manager->sessions = realloc(manager->sessions, (manager->sessionCount + 1) * sizeof(Session));
    Session *newSession = &manager->sessions[manager->sessionCount++];
    strcpy(newSession->sessionId, generateUUID());
    strcpy(newSession->username, username);
    return newSession->sessionId;
}

char *getUsername(SessionManager *manager, const char *sessionId) {
    for (size_t i = 0; i < manager->sessionCount; ++i) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            return manager->sessions[i].username;
        }
    }
    return NULL;
}

void invalidateSession(SessionManager *manager, const char *sessionId) {
    for (size_t i = 0; i < manager->sessionCount; ++i) {
        if (strcmp(manager->sessions[i].sessionId, sessionId) == 0) {
            for (size_t j = i; j < manager->sessionCount - 1; ++j) {
                manager->sessions[j] = manager->sessions[j + 1];
            }
            manager->sessions = realloc(manager->sessions, (--manager->sessionCount) * sizeof(Session));
            break;
        }
    }
}

// Test cases
int main() {
    srand(time(0));
    SessionManager sessionManager;
    initSessionManager(&sessionManager);
    
    char *session1 = createSession(&sessionManager, "user1");
    printf("%s\n", getUsername(&sessionManager, session1));  // Should print "user1"
    
    char *session2 = createSession(&sessionManager, "user2");
    printf("%s\n", getUsername(&sessionManager, session2));  // Should print "user2"
    
    invalidateSession(&sessionManager, session1);
    printf("%s\n", getUsername(&sessionManager, session1));  // Should print "(null)"
    
    char *session3 = createSession(&sessionManager, "user3");
    printf("%s\n", getUsername(&sessionManager, session3));  // Should print "user3"
    
    invalidateSession(&sessionManager, session2);
    printf("%s\n", getUsername(&sessionManager, session2));  // Should print "(null)"
    
    free(sessionManager.sessions);
    return 0;
}