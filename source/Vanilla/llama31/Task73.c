#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool isValidPassword(const char* password) {
    if (strlen(password) < 10) return 0;
    bool hasUppercase = 0, hasNumber = 0, hasSpecialChar = 0;
    for (int i = 0; i < strlen(password); i++) {
        char c = password[i];
        if (isupper(c)) hasUppercase = 1;
        else if (isdigit(c)) hasNumber = 1;
        else if (!isalnum(c)) hasSpecialChar = 1;
    }
    return hasUppercase && hasNumber && hasSpecialChar;
}

int main() {
    const char* testCases[] = {"Passw0rd!", "password123", "P@ssw0rd!", "short", "NoSpecialChar123"};
    for (int i = 0; i < 5; i++) {
        printf("Password: %s - Valid: %s\n", testCases[i], isValidPassword(testCases[i]) ? "true" : "false");
    }
    return 0;
}