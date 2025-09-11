#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note:  C does not have built-in hash maps or UUID generation.  This is a simplified example 
// and would require more robust implementations for production use.  For UUIDs, consider
// a third-party library or generating them differently.  For hash maps, you might use
// a library or implement your own.

typedef struct {
    char username[50]; // Fixed size for simplicity
} UserSession;

typedef struct {
    char sessionId[50]; // Fixed size for simplicity.
    UserSession session;
} SessionEntry;


// Very basic session management (array implementation. NOT PRODUCTION READY)
SessionEntry sessions[100]; // Fixed-size array.  Not ideal.
int sessionCount = 0;


char* createSession(const char* username) {
    if (sessionCount < 100) {  // Prevent overflow
        char sessionId[50]; // Should be a UUID ideally
        sprintf(sessionId, "%d", sessionCount); // Placeholder ID

        strcpy(sessions[sessionCount].sessionId, sessionId);
        strcpy(sessions[sessionCount].session.username, username);

        sessionCount++;
        return strdup(sessionId); // Return a copy
    }
    return NULL;
}


UserSession* getSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            return &sessions[i].session;
        }
    }
    return NULL;
}


void invalidateSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            //  Simple removal (shift elements). Not efficient for large numbers of sessions.
            for (int j = i; j < sessionCount - 1; j++) {
                sessions[j] = sessions[j + 1];
            }
            sessionCount--;
            return;
        }
    }
}

int main() {
     // Test Cases:
    char* sessionId1 = createSession("user1");
    printf("Session 1 ID: %s\n", sessionId1);

    char* sessionId2 = createSession("user2");
    printf("Session 2 ID: %s\n", sessionId2);

    UserSession* user1Session = getSession(sessionId1);
    if (user1Session) {
        printf("User 1 name: %s\n", user1Session->username);
    }

    invalidateSession(sessionId1);

     user1Session = getSession(sessionId1); // should be null after invalidation

     if (user1Session) {
        printf("User 1 name: %s\n", user1Session->username);
    } else {
        printf("Session 1 invalidated.\n"); 
    }


    char* sessionId3 = createSession("user3");
    printf("Session 3 ID: %s\n", sessionId3);


    char* sessionId4 = createSession("user4");
    printf("Session 4 ID: %s\n", sessionId4);

    free(sessionId1); // Free the dynamically allocated memory (strdup)
    free(sessionId2);
    free(sessionId3);
    free(sessionId4);

    return 0;
}