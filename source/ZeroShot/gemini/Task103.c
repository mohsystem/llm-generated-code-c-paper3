#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isStrongPassword(const char *password) {
    if (strlen(password) < 8) {
        return false;
    }
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            hasUpper = true;
        } else if (islower(password[i])) {
            hasLower = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }
    return hasUpper && hasLower && hasDigit;
}

int main() {
    printf("%d\n", isStrongPassword("short")); // 0 (false)
    printf("%d\n", isStrongPassword("noNumbers")); // 0 (false)
    printf("%d\n", isStrongPassword("NoDigits")); // 0 (false)
    printf("%d\n", isStrongPassword("NoUpperCase1")); // 0 (false)
    printf("%d\n", isStrongPassword("CorrectPassword1")); // 1 (true)
    return 0;
}