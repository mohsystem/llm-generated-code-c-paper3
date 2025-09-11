#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Note:  C doesn't have built-in hash maps, so a simplified demonstration is provided.
// For a real application, use a proper hash map library.


typedef struct {
    char username[50]; // Fixed-size username for simplicity.  Use dynamic allocation in real code.
    
} UserSession;

// Very basic and insecure session management for demo.  Do not use in production.
UserSession sessions[100];  // Fixed-size array, extremely limited.
int sessionCount = 0;

char* createSession(const char* username) {
    if (sessionCount < 100) {  // Prevent overflow
        strcpy(sessions[sessionCount].username, username);
        char* sessionId = malloc(10 * sizeof(char)); // Allocate memory for session ID (basic example)
        sprintf(sessionId, "%d", sessionCount);  // Simple session ID, very insecure
        sessionCount++;
        return sessionId;
    }
    return NULL; // Error: session limit reached
}


bool isValidSession(const char* sessionId) {
    int id = atoi(sessionId); // Convert string to integer
    return (id >= 0 && id < sessionCount);
}

char* getUsername(const char* sessionId) {
    if (isValidSession(sessionId)) {
        int id = atoi(sessionId);
        return sessions[id].username;
    }
    return NULL;
}


void invalidateSession(const char* sessionId) {
    // In this simplified example, invalidation is a no-op as we don't have proper memory management.
    // In a real application, you would free the associated memory and remove the session from the data structure.

}


int main() {
    char* session1 = createSession("user1");
    char* session2 = createSession("user2");


    printf("Session 1 valid: %s\n", isValidSession(session1) ? "true" : "false"); // True
    printf("Session 2 valid: %s\n", isValidSession(session2) ? "true" : "false"); // True
    printf("Session 1 username: %s\n", getUsername(session1)); // user1

    invalidateSession(session1);

    printf("Session 1 valid after invalidation: %s\n", isValidSession(session1) ? "true" : "false");  // Still "true" in this simplified example because we haven't actually removed it.
    printf("Session 2 username: %s\n", getUsername(session2)); // user2

    free(session1); // Free allocated memory
    free(session2);


    return 0;
}