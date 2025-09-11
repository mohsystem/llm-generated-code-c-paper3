// C code
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool isValidPassword(const char* password) {
    if (strlen(password) < 6 || strlen(password) > 20) {
        return false;
    }
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    const char* specialChars = "!@#$%^&*()_+-={}:<>?,./";
    for (int i = 0; i < strlen(password); i++) {
        char c = password[i];
        if (isupper(c)) {
            hasUppercase = true;
        } else if (islower(c)) {
            hasLowercase = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        } else if (strchr(specialChars, c) != NULL) {
            hasSpecial = true;
        }
    }
    return hasUppercase && hasLowercase && hasDigit && hasSpecial;
}

int main() {
    const char* testCases[] = {"Geek12#", "asd123", "Password123!", "short", "VeryLongPasswordThatIsNotValidBecauseItIsTooLong"};
    for (int i = 0; i < 5; i++) {
        if (isValidPassword(testCases[i])) {
            printf("%s - Valid Password\n", testCases[i]);
        } else {
            printf("%s - Invalid Password\n", testCases[i]);
        }
    }
    return 0;
}