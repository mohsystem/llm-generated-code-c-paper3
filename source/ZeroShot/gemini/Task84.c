#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Note: This C implementation uses a less secure random number generator
//       for demonstration purposes because a secure random number 
//       generator is not readily portable in standard C. For production,
//       use a cryptographically secure random number generator.

char* generateSessionId() {
    char* sessionId = (char*)malloc(25 * sizeof(char)); // 24 bytes + null terminator
    srand(time(NULL)); // Seed the random number generator. NOT SECURE for production.
    for (int i = 0; i < 24; i++) {
        sessionId[i] = 'a' + (rand() % 26); // Generate random lowercase letters. NOT SECURE.
    }
    sessionId[24] = '\0';
    return sessionId;

}

int main() {
    for (int i = 0; i < 5; i++) {
        char* id = generateSessionId();
        printf("%s\n", id);
        free(id); // Free the allocated memory
    }
    return 0;

}