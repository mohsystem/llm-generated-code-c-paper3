#include <stdio.h>
#include <string.h>
#include <regex.h>

int validateInput(const char *input, const char *regexPattern) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex, regexPattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }
    reti = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

int main() {
    printf("%d\n", validateInput("test@example.com", "^[A-Za-z0-9+_.-]+@(.+)$")); // 1
    printf("%d\n", validateInput("123-456-7890", "^[0-9]{3}-[0-9]{3}-[0-9]{4}$")); // 1
    printf("%d\n", validateInput("invalid-email", "^[A-Za-z0-9+_.-]+@(.+)$")); // 0
    printf("%d\n", validateInput("123456", "^[0-9]{3}-[0-9]{3}-[0-9]{4}$")); // 0
    printf("%d\n", validateInput("TestUser123", "^[A-Za-z0-9]+$")); // 1
    return 0;
}