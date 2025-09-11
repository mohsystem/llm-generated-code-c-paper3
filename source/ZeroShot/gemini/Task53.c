#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simplified session management (not thread-safe)
typedef struct {
    char sessionId[33]; // Store session ID as string
    char username[256]; 
} UserSession;

UserSession sessions[100]; // Example: max 100 sessions
int sessionCount = 0;


char* createSession(const char* username) {
    if (sessionCount >= 100) {
        return NULL; // Session limit reached
    }

    // Generate a simple random session ID (replace with more robust method)
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < 32; i++) {
        sessions[sessionCount].sessionId[i] = 'a' + (rand() % 26); // Random lowercase letters
    }
    sessions[sessionCount].sessionId[32] = '\0'; 

    strncpy(sessions[sessionCount].username, username, sizeof(sessions[sessionCount].username) -1);
    sessions[sessionCount].username[sizeof(sessions[sessionCount].username) - 1] = '\0';

    sessionCount++;
    return sessions[sessionCount - 1].sessionId;
}

UserSession* getSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            return &sessions[i];
        }
    }
    return NULL;
}

void invalidateSession(const char* sessionId) {
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].sessionId, sessionId) == 0) {
            // Remove session by shifting remaining sessions
            for (int j = i; j < sessionCount - 1; j++) {
                sessions[j] = sessions[j + 1];
            }
            sessionCount--;
            return;
        }
    }
}

int main() {
    char* session1 = createSession("user1");
    char* session2 = createSession("user2");

    printf("Session 1: %s, Username: %s\n", session1, getSession(session1)->username);
    printf("Session 2: %s, Username: %s\n", session2, getSession(session2)->username);

    invalidateSession(session1);


    UserSession* s1 = getSession(session1);
    if (s1) {
         printf("Session 1: %s, Username: %s\n", s1->sessionId, s1->username); // Should be empty
    } else {
        printf("Session 1 not found\n");
    }

     printf("Session 2: %s, Username: %s\n", session2, getSession(session2)->username);

    char* session3 = createSession("user3");
    char* session4 = createSession("user4");
    char* session5 = createSession("user5");

    printf("Session 3: %s, Username: %s\n", session3, getSession(session3)->username);
    printf("Session 4: %s, Username: %s\n", session4, getSession(session4)->username);
    printf("Session 5: %s, Username: %s\n", session5, getSession(session5)->username);

    return 0;
}