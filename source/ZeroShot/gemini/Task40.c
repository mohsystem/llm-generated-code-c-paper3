// c code here:
//  Requires a web framework (e.g., CGI) for a full implementation.
//  This example demonstrates core CSRF protection logic.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Simplified session storage (replace with actual session management) — This is insecure and just for basic illustration.
//  Do not use this in a production environment.
char sessions[100][100];  // Highly insecure.  Do not use this in production!
int sessionCount = 0;


// Function to generate a random CSRF token
char* generateCSRFToken() {
    char* token = malloc(33 * sizeof(char)); // Allocate memory for the token
    if (token == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    const char characters[] = "0123456789abcdef";
    srand(time(NULL));
    for (int i = 0; i < 32; i++) {
        token[i] = characters[rand() % 16];
    }
    token[32] = '\0';
    return token;
}

//  Highly insecure verification - do not use in production. For illustrative purposes only.
int verifyCSRFToken(const char* sessionId, const char* csrfToken) {

    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i], sessionId) == 0) {
             // Very insecure string comparison – replace with constant-time comparison in production
            return strcmp(sessions[i+1], csrfToken) == 0;  
        }
    }
    return 0;
}

// Simulated web request handling (replace with actual framework code)
void handleUpdateSettings(const char* method, const char* sessionId, const char* csrfToken) {

    if (strcmp(method, "GET") == 0) {
        char* token = generateCSRFToken();

         // Insecure - Fix for production code
        strcpy(sessions[sessionCount++], sessionId);
        strcpy(sessions[sessionCount++], token);

        printf("<form method='post'><input type='hidden' name='csrf_token' value='%s'><button>Submit</button></form>", token);
        free(token);


    } else if (strcmp(method, "POST") == 0) {
        if (verifyCSRFToken(sessionId, csrfToken)) {
            printf("Settings updated\n");
        } else {
            printf("CSRF attack detected!\n");
        }
    }
}

int main() {
    // Test cases
    const char* sessionId = "test_session";

    // Test 1: Valid CSRF token
    handleUpdateSettings("GET", sessionId, "");
    char * form = sessions[sessionCount-1];

    handleUpdateSettings("POST", sessionId, form); // Expected: Settings updated

    // Test 2: Invalid CSRF token
    handleUpdateSettings("POST", sessionId, "invalid_token"); // Expected: CSRF attack detected!

    // Test 3: No CSRF token
    handleUpdateSettings("POST", sessionId, ""); // Expected: CSRF attack detected!

    return 0;
}