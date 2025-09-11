#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool checkPasswordStrength(const char* password) {
    if (strlen(password) < 8) {
        return false;
    }
    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            hasUpperCase = true;
        } else if (islower(password[i])) {
            hasLowerCase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }
    return hasUpperCase && hasLowerCase && hasDigit;
}

int main() {
    printf("%d\n", checkPasswordStrength("Password123")); // 1
    printf("%d\n", checkPasswordStrength("password"));    // 0
    printf("%d\n", checkPasswordStrength("PASSWORD123")); // 0
    printf("%d\n", checkPasswordStrength("Pass123"));     // 0
    printf("%d\n", checkPasswordStrength("Passw0rd"));    // 1
    return 0;
}