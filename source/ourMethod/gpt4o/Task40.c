#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateCSRFToken() {
    srand(time(0));
    static char token[37];
    snprintf(token, sizeof(token), "%d", rand());
    return token;
}

int validateCSRFToken(const char* tokenFromRequest, const char* tokenFromSession) {
    return strcmp(tokenFromRequest, tokenFromSession) == 0;
}

const char* updateUserSettings(const char* username, const char* email, const char* csrfToken, const char* sessionToken) {
    if (validateCSRFToken(csrfToken, sessionToken)) {
        static char message[100];
        snprintf(message, sizeof(message), "Settings updated for user: %s", username);
        return message;
    } else {
        return "CSRF token validation failed.";
    }
}

int main() {
    printf("%s\n", generateCSRFToken());
    printf("%d\n", validateCSRFToken("12345", "12345"));
    printf("%s\n", updateUserSettings("username", "email@example.com", "validToken", "validToken"));
    printf("%s\n", updateUserSettings("username", "email@example.com", "invalidToken", "validToken"));
    return 0;
}