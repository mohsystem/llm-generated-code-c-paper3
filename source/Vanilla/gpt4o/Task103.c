#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool checkPasswordStrength(const char* password) {
    if (strlen(password) < 8) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false;

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = true;
        if (islower(password[i])) hasLower = true;
        if (isdigit(password[i])) hasDigit = true;
    }
    
    return hasUpper && hasLower && hasDigit;
}

int main() {
    printf("%d\n", checkPasswordStrength("Password1")); // true
    printf("%d\n", checkPasswordStrength("password1")); // false
    printf("%d\n", checkPasswordStrength("PASSWORD1")); // false
    printf("%d\n", checkPasswordStrength("Pass1"));     // false
    printf("%d\n", checkPasswordStrength("PassWord123")); // true
    return 0;
}