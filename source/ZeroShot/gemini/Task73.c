#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isValidAdminPassword(const char *password) {
    if (password == NULL || strlen(password) < 12) {
        return false;
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    const char *specialChars = "!@#$%^&*()-_=+[]{}|;:'\",.<>/?";

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            hasUppercase = true;
        } else if (islower(password[i])) {
            hasLowercase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        } else {
            for (int j = 0; specialChars[j] != '\0'; j++) {
                if (password[i] == specialChars[j]) {
                    hasSpecialChar = true;
                    break;
                }
            }
        }
    }

    return hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

int main() {
    printf("%d\n", isValidAdminPassword("Short")); // false
    printf("%d\n", isValidAdminPassword("NoSpecialChars123")); // false
    printf("%d\n", isValidAdminPassword("AllLowercase123!")); // false
    printf("%d\n", isValidAdminPassword("ALLUPPERCASE123!")); // false
    printf("%d\n", isValidAdminPassword("ValidPassword123!")); // true
    return 0;
}