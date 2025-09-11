#include <stdio.h>
#include <stdbool.h>
#include <regex.h>

bool isValidPassword(char* password) {
    // Length check
    if (strlen(password) < 8) {
        return false;
    }

    // Contains at least one uppercase letter, one lowercase letter, one number, and one special character
    regex_t regex;
    int reti = regcomp(&regex, "(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*[!@#$%^&*()])", REG_EXTENDED);
    if (reti) {
        return false;
    }

    reti = regexec(&regex, password, 0, NULL, 0);
    regfree(&regex);
    if (reti) {
        return false;
    }

    return true;
}

int main() {
    printf("%d\n", isValidPassword("Admin@123")); // 1 (true)
    printf("%d\n", isValidPassword("admin123")); // 0 (false)
    printf("%d\n", isValidPassword("Admin123")); // 0 (false)
    printf("%d\n", isValidPassword("Admin@")); // 0 (false)
    printf("%d\n", isValidPassword("Admin@12345678")); // 1 (true)
    return 0;
}