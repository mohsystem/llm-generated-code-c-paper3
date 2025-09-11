#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidPassword(const char* password) {
    if (strlen(password) < 8) {
        return 0;
    }
    int hasUpperCase = 0;
    int hasLowerCase = 0;
    int hasDigit = 0;

    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) {
            hasUpperCase = 1;
        } else if (islower(password[i])) {
            hasLowerCase = 1;
        } else if (isdigit(password[i])) {
            hasDigit = 1;
        }
    }

    return hasUpperCase && hasLowerCase && hasDigit;
}

int main() {
    const char* testCases[] = {"Password123", "password123", "PASSWORD123", "P@ssw0rd", "Abcdefgh"};
    for (int i = 0; i < 5; i++) {
        if (isValidPassword(testCases[i])) {
            printf("%s: Valid Password\n", testCases[i]);
        } else {
            printf("%s: Invalid Password\n", testCases[i]);
        }
    }
    return 0;
}