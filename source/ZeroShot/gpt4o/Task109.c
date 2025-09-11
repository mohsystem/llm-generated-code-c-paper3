#include <stdio.h>
#include <regex.h>
#include <stdbool.h>

bool validateInput(const char *input, const char *regexPattern) {
    regex_t regex;
    int result;
    bool match = false;

    result = regcomp(&regex, regexPattern, REG_EXTENDED);
    if (result == 0) {
        result = regexec(&regex, input, 0, NULL, 0);
        match = (result == 0);
    }
    regfree(&regex);
    return match;
}

int main() {
    printf("%d\n", validateInput("abc123", "^[a-zA-Z0-9]+$")); // true
    printf("%d\n", validateInput("abc!123", "^[a-zA-Z0-9]+$")); // false
    printf("%d\n", validateInput("hello@example.com", "^[\\w-.]+@([\\w-]+\\.)+[\\w-]{2,4}$")); // true
    printf("%d\n", validateInput("helloexample.com", "^[\\w-.]+@([\\w-]+\\.)+[\\w-]{2,4}$")); // false
    printf("%d\n", validateInput("12345", "^\\d+$")); // true
    return 0;
}