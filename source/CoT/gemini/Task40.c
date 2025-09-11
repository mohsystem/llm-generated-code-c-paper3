#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simplified example.  A real web application would use a web framework
// and handle HTTP requests/responses properly.  This code demonstrates 
// the core CSRF protection logic.

//  Very basic (insecure for production) example of token generation.
// In a real application, use a cryptographically secure random number generator.
char* generateCsrfToken() {
    char* token = malloc(33 * sizeof(char)); // 32 characters + null terminator
    srand(time(NULL));  // Initialize random seed
    for (int i = 0; i < 32; i++) {
        token[i] = "0123456789abcdef"[rand() % 16];
    }
    token[32] = '\0';
    return token;
}


int verifyCsrfToken(const char* requestToken, const char* sessionToken) {
    return strcmp(requestToken, sessionToken) == 0;
}

int main() {
     // Simulated HTTP requests for demonstration
    char* sessionToken = generateCsrfToken();

    // Simulate a valid form submission
    char* validRequestToken = strdup(sessionToken); // Create a copy
    if (verifyCsrfToken(validRequestToken, sessionToken)) {
        printf("Settings updated successfully (Valid request).\n");
    } else {
        printf("CSRF attack detected! (Valid request)\n");
    }

    free(validRequestToken); // Free the copy


    // Simulate an invalid form submission (CSRF attack)
    char* invalidRequestToken = generateCsrfToken();
    if (verifyCsrfToken(invalidRequestToken, sessionToken)) {
         printf("Settings updated successfully (Invalid request).\n");
    } else {
        printf("CSRF attack detected! (Invalid request)\n");
    }


    free(invalidRequestToken);
    free(sessionToken);

    return 0;
}