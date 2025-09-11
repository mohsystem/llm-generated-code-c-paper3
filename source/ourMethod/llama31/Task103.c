#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool checkPasswordStrength(const char* password) {
    if (strlen(password) < 8) {
        return false;
    }
    bool hasLower = false, hasUpper = false, hasDigit = false;
    for (int i = 0; password[i] != '\0'; ++i) {
        if (islower(password[i])) {
            hasLower = true;
        } else if (isupper(password[i])) {
            hasUpper = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }
    return hasLower && hasUpper && hasDigit;
}

int main() {
    const char* testCases[] = {"Password123", "password123", "PASSWORD123", "P@ssw0rd", "short"};
    for (int i = 0; i < 5; ++i) {
        if (checkPasswordStrength(testCases[i])) {
            printf("Password '%s' is strong.\n", testCases[i]);
        } else {
            printf("Password '%s' is weak.\n", testCases[i]);
        }
    }
    return 0;
}