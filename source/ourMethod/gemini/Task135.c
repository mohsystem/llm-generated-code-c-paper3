#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Mock session storage (replace with actual session management)
typedef struct {
    char csrfToken[64]; // Increased size to hold encoded token
} Session;

Session sessions[10]; // Example session storage
int sessionCount = 0;

char* generateCsrfToken() {
    int i;
    char token[32];
    srand(time(NULL)); // Seed the random number generator

    for (i = 0; i < 32; i++) {
        token[i] = (char)(rand() % 256); 
    }

    char* encodedToken = (char*)malloc(64 * sizeof(char)); // Allocate memory for encoded token
    if (encodedToken == NULL) {
        return NULL; // Handle memory allocation error
    }
    //Base64 encoding (replace with a robust implementation if needed)
    // ... Base64 encoding logic here ...

    if (sessionCount < 10) {
        strcpy(sessions[sessionCount].csrfToken, encodedToken);
    }

    return encodedToken;
}


int validateCsrfToken(int sessionId, const char* requestToken) {
    if (sessionId < 0 || sessionId >= sessionCount || requestToken == NULL) {
        return 0; 
    }

    return strcmp(sessions[sessionId].csrfToken, requestToken) == 0;
}

int main() {
    char* token1 = generateCsrfToken();
    printf("Test 1: %d\n", validateCsrfToken(sessionCount -1, token1)); // Expected: true
    free(token1);

    generateCsrfToken();
    printf("Test 2: %d\n", validateCsrfToken(sessionCount -1, "invalid_token")); // Expected: false

    printf("Test 3: %d\n", validateCsrfToken(100, "")); // Expected: false

    char *token4 = generateCsrfToken();
    sessions[sessionCount] = sessions[sessionCount - 1];
    sessionCount++;
    printf("Test 4: %d\n", validateCsrfToken(sessionCount - 1, token4)); // Expected: true
    free(token4);

    generateCsrfToken();
    printf("Test 5: %d\n", validateCsrfToken(sessionCount - 1, NULL)); // Expected: false

    return 0;
}