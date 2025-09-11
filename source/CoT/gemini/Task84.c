#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Note: This C implementation uses a simpler approach for generating
// session IDs and does not include Base64 encoding. For stronger 
// uniqueness, consider using a library for UUID generation.


char* generateSessionId() {
    char* sessionId = (char*)malloc(33 * sizeof(char)); 
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < 32; i++) {
        sessionId[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    sessionId[32] = '\0';
    return sessionId;
}

int main() {

    char* sessionIds[5];
    for (int i = 0; i < 5; i++) {
        sessionIds[i] = generateSessionId();
        // Basic duplicate check (not robust for large numbers of IDs)
        for(int j = 0; j < i; j++) {
            if(strcmp(sessionIds[i], sessionIds[j]) == 0) {
                 fprintf(stderr, "Error: Duplicate session ID generated.\n");
                 return 1; 
            }
        }
        printf("Generated Session ID %d: %s\n", i + 1, sessionIds[i]);
        free(sessionIds[i]);
    }

    return 0;
}