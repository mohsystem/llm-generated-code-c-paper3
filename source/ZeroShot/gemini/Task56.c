#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note: This C implementation uses a less secure random number generator
// For production, use a cryptographically secure random number generator.

char* generateToken() {
    char* token = (char*)malloc(45 * sizeof(char)); // Increased for potential padding
    char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

    for (int i = 0; i < 43; i++) {  // Adjusted length to exclude potential padding
        token[i] = chars[rand() % 62];
    }
    token[43] = '\0'; // Null-terminate the string
    return token;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* token = generateToken();
        printf("Generated Token %d: %s\n", i + 1, token);
        free(token); // Free the allocated memory
    }
    return 0;
}