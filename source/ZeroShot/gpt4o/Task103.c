#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isStrongPassword(const char *password) {
    if (strlen(password) < 8) {
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = true;
        if (islower(password[i])) hasLower = true;
        if (isdigit(password[i])) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

int main() {
    printf("%d\n", isStrongPassword("Password1")); // 1
    printf("%d\n", isStrongPassword("password1")); // 0
    printf("%d\n", isStrongPassword("PASSWORD1")); // 0
    printf("%d\n", isStrongPassword("Pass1"));     // 0
    printf("%d\n", isStrongPassword("Pass1234"));  // 1
    return 0;
}