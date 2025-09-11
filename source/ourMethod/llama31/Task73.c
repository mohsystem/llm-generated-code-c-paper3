#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isValidPassword(const char* password) {
    if (strlen(password) < 6 || strlen(password) > 20) {
        return 0;
    }
    int hasUppercase = 0;
    int hasLowercase = 0;
    int hasDigit = 0;
    int hasSpecialChar = 0;

    for (int i = 0; password[i]; ++i) {
        if (isupper(password[i])) {
            hasUppercase = 1;
        } else if (islower(password[i])) {
            hasLowercase = 1;
        } else if (isdigit(password[i])) {
            hasDigit = 1;
        } else if (!isalnum(password[i])) {
            hasSpecialChar = 1;
        }
    }

    return hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

int main() {
    const char* testPasswords[] = {"Geek12#", "asd123", "Password123!", "P@ssw0rd", "Invalid"};
    for (int i = 0; i < 5; ++i) {
        if (isValidPassword(testPasswords[i])) {
            printf("%s - Valid Password\n", testPasswords[i]);
        } else {
            printf("%s - Invalid Password\n", testPasswords[i]);
        }
    }
    return 0;
}