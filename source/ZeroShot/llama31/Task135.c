#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Simple random string generator for CSRF token
char* generateCSRFToken() {
    static char token[37];
    srand(time(NULL));
    for (int i = 0; i < 36; ++i) {
        token[i] = "0123456789abcdef"[rand() % 16];
    }
    token[36] = '\0';
    return token;
}

bool validateCSRFToken(const char* actualToken, const char* expectedToken) {
    return strcmp(actualToken, expectedToken) == 0;
}

int main() {
    char* csrfToken = generateCSRFToken();
    printf("Generated CSRF Token: %s\n", csrfToken);

    // Simulate request with token
    const char* actualToken = csrfToken;
    bool isValid = validateCSRFToken(actualToken, csrfToken);
    printf("Is CSRF token valid? %s\n", isValid ? "Yes" : "No");

    // Test cases
    const char* testCases[] = {"valid-token", "invalid-token", "valid-token", "", "valid-token"};
    for (const char* testCase : testCases) {
        isValid = validateCSRFToken(testCase, csrfToken);
        printf("Test Case: %s, Is CSRF token valid? %s\n", testCase, isValid ? "Yes" : "No");
    }

    return 0;
}