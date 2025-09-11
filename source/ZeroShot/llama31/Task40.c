// Note: C is not typically used for web development. This is a conceptual example.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generateCSRFToken() {
    char* token = malloc(33 * sizeof(char));
    srand(time(NULL));
    for (int i = 0; i < 32; ++i) {
        token[i] = "0123456789ABCDEF"[rand() % 16];
    }
    token[32] = '\0';
    return token;
}

void processFormData() {
    // Process form data here
}

int main() {
    char* csrfToken = generateCSRFToken();
    // Simulate setting token in session

    // Simulate getting tokens from request and session
    char* csrfTokenFromSession = "token_from_session";
    char* csrfTokenFromRequest = "token_from_request";

    if (strcmp(csrfTokenFromSession, csrfTokenFromRequest) == 0) {
        processFormData();
        printf("Form data processed successfully\n");
    } else {
        printf("CSRF attack detected\n");
    }

    free(csrfToken);
    return 0;
}