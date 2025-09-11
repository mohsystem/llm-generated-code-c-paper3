#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isPasswordStrong(const char* password) {
    if (password == NULL || strlen(password) < 8) return false;

    bool hasUpper = false, hasLower = false, hasDigit = false;

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = true;
        if (islower(password[i])) hasLower = true;
        if (isdigit(password[i])) hasDigit = true;
    }

    return hasUpper && hasLower && hasDigit;
}

int main() {
    printf("%d\n", isPasswordStrong("Password1")); // 1
    printf("%d\n", isPasswordStrong("password1")); // 0
    printf("%d\n", isPasswordStrong("PASSWORD1")); // 0
    printf("%d\n", isPasswordStrong("Pass1"));     // 0
    printf("%d\n", isPasswordStrong("PassWord1")); // 1

    return 0;
}