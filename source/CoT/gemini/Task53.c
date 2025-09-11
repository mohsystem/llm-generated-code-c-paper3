#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simplified session management for C example (no hashmap)
//  In real application, use a proper hashmap or similar.

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 32

typedef struct {
    char sessionId[SESSION_ID_LENGTH + 1];
    char username[50]; // Adjust size as needed
    // Add more session data as required.
} UserSession;

UserSession sessions[MAX_SESSIONS];
int sessionCount = 0;

// Generates a simple random session ID (Not cryptographically secure)
// For production, use a better random ID generator.
void generateSessionId(char *sessionId) {
    const char charset[] = "0123456789abcdef";
    srand(time(NULL)); //Seed the random number generator
    for (int i = 0; i < SESSION_ID_LENGTH; i++) {
        sessionId[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    sessionId[SESSION_ID_LENGTH] = '\0';
}


char* createSession(const char *username) {
    if (sessionCount < MAX_SESSIONS) {
        UserSession *session = &sessions[sessionCount++];
        generateSessionId(session->sessionId);
        strncpy(session->username, username, sizeof(session->username) -1);
        session->username[sizeof(session->username) - 1] = '\0'; // Ensure null termination
        return session->sessionId;
    }
    return NULL; // Or handle error as appropriate
}

UserSession* getSession(const char *sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            return &sessions[i];
        }
    }
    return NULL;
}

void invalidateSession(const char *sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            // "Remove" by shifting remaining sessions
            for (int j = i; j < sessionCount - 1; j++) {
                sessions[j] = sessions[j + 1];
            }
            sessionCount--;
            return;
        }
    }
}


int main() {
    // Test cases
    char* sessionId1 = createSession("user1");
    printf("Session 1 created: %s\n", sessionId1);
    UserSession* session1 = getSession(sessionId1);
     if (session1 != NULL) {
        printf("Session 1 username: %s\n", session1->username);
    }


    char* sessionId2 = createSession("user2");
    printf("Session 2 created: %s\n", sessionId2);
    UserSession* session2 = getSession(sessionId2);
     if (session2 != NULL) {
        printf("Session 2 username: %s\n", session2->username);
    }


    invalidateSession(sessionId1);
    printf("Session 1 invalidated:\n");
    session1 = getSession(sessionId1); //session1 should be NULL now
    if(session1 == NULL){
        printf("Session 1 not found\n");
    }



    char* sessionId3 = createSession("user3");
    printf("Session 3 created: %s\n", sessionId3);
    UserSession* session3 = getSession(sessionId3);
     if (session3 != NULL) {
        printf("Session 3 username: %s\n", session3->username);
    }


    char* sessionId4 = createSession("user4");
    printf("Session 4 created: %s\n", sessionId4);
    UserSession* session4 = getSession(sessionId4);
     if (session4 != NULL) {
        printf("Session 4 username: %s\n", session4->username);
    }


    char* sessionId5 = createSession("user5");
    printf("Session 5 created: %s\n", sessionId5);
    UserSession* session5 = getSession(sessionId5);
     if (session5 != NULL) {
        printf("Session 5 username: %s\n", session5->username);
    }


    return 0;
}