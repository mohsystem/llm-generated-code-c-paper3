#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generateCsrfToken() {
    char* token = malloc(33 * sizeof(char));
    srand(time(NULL));
    for (int i = 0; i < 32; i++) {
        token[i] = "0123456789abcdef"[rand() % 16];
    }
    token[32] = '\0';
    return token;
}

int validateCsrfToken(const char* expectedToken, const char* actualToken) {
    return strcmp(expectedToken, actualToken) == 0;
}

int main() {
    // Test cases
    printf("C CSRF Protection\n");
    char* token = generateCsrfToken();
    printf("Generated Token: %s\n", token);
    int isValid = validateCsrfToken(token, token);
    printf("Is Token Valid? %s\n", isValid ? "true" : "false");
    free(token);
    return 0;
}