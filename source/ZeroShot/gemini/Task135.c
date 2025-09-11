#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simplified Example (Requires web framework for real CSRF protection)

//  Function to generate a CSRF token
char* generate_csrf_token() {
    char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int len = 32; // Length of the token
    char *token = (char *) malloc(sizeof(char) * (len + 1));
    if (token == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < len; i++) {
        token[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    token[len] = '\0';
    return token;
}


// Function to verify the CSRF token
int verify_csrf_token(const char* stored_token, const char* request_token) {
    if (stored_token == NULL || request_token == NULL) {
        return 0; // Handle NULL pointers safely
    }
    return strcmp(stored_token, request_token) == 0;
}

int main() {
     char *token = generate_csrf_token();
     if (token != NULL) {
         printf("Generated token: %s\n", token);
         
        // Example verification
        char request_token[33]; // Make sure it's large enough
        strcpy(request_token, token);  // Correct token for testing
        int valid = verify_csrf_token(token, request_token);
        printf("Valid token verification: %d\n", valid); // Should print 1

        strcpy(request_token, "invalid_token"); // Incorrect token
        valid = verify_csrf_token(token, request_token);
        printf("Invalid token verification: %d\n", valid); // Should print 0
         
         free(token); // Free allocated memory

     }
     return 0;
}