#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Basic random string generation (not cryptographically secure)
char* generateSessionId() {
    char* sessionId = (char*)malloc(33 * sizeof(char)); // Allocate memory for the session ID
    if (sessionId == NULL) {
        return NULL; // Handle memory allocation failure
    }

    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < 32; ++i) {
        sessionId[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    sessionId[32] = '\0'; // Null-terminate the string
    return sessionId;
}

int main() {

    char *sessionIds[5];
    for (int i = 0; i < 5; i++) {
        sessionIds[i] = generateSessionId();
         for(int j=0; j<i; j++){ //check for duplication
            if(strcmp(sessionIds[i], sessionIds[j]) == 0){
                printf("Error: Duplicate session ID generated.\n");
                return 1;
            }
         }
        printf("Generated Session ID %d: %s\n", i + 1, sessionIds[i]);
        free(sessionIds[i]); // Free the allocated memory
    }

    return 0;
}