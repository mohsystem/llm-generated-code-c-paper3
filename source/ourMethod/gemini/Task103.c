#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isStrongPassword(char *password) {
    int len = strlen(password);

    if (len < 8) {
        return false;
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;


    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) {
            hasUpper = true;
        }
        if (islower(password[i])) {
            hasLower = true;
        }
        if (isdigit(password[i])) {
            hasDigit = true;
        }
    }

    return hasUpper && hasLower && hasDigit;
}

int main() {
    printf("%d\n", isStrongPassword("Test1")); // false
    printf("%d\n", isStrongPassword("TestTest1")); // true
    printf("%d\n", isStrongPassword("Testtest")); // false
    printf("%d\n", isStrongPassword("TestTest")); // false
    printf("%d\n", isStrongPassword("Test1234"));// false
    return 0;
}