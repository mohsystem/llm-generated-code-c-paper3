#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Note: C web frameworks (e.g., Onion) are highly recommended for robust session management.
// This example illustrates basic principles without a web framework.

// Very basic (insecure) session ID generation.  Do not use in production.
char* generateSessionId() {
    char *sessionId = malloc(33 * sizeof(char)); // Allocate memory for session ID

    if (sessionId == NULL) {
      return NULL; // Handle memory allocation failure
    }

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(NULL)); // Seed the random number generator 

    for (int i = 0; i < 32; i++) {
        sessionId[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    sessionId[32] = '\0'; // Null-terminate the string
    return sessionId;
}

int main() {
     // Simulated session (replace with actual web framework usage)
    char *sessionId = NULL;

    for (int i = 0; i < 5; ++i) {

        if (sessionId == NULL) {
            sessionId = generateSessionId();
            if (sessionId != NULL) {
              printf("New session created with ID: %s\n", sessionId);
            } else {
              perror("Failed to allocate memory for session ID");
              return 1; // Indicate an error
            }

        } else {
            printf("Existing session with ID: %s\n", sessionId);
        }

        // Simulate logout
        if (i == 2) {
            free(sessionId); // Free the dynamically allocated memory
            sessionId = NULL;
        }
    }
     if (sessionId != NULL) {
        free(sessionId);
    }
    return 0;
}