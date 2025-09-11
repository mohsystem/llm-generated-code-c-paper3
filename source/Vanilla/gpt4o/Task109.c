#include <stdio.h>
#include <regex.h>

int validateInput(const char *input, const char *pattern) {
    regex_t regex;
    int result;
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        return 0;
    }
    result = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    return !result;
}

int main() {
    printf("%d\n", validateInput("abc123", "\\w+")); // 1
    printf("%d\n", validateInput("123-456", "\\d{3}-\\d{3}")); // 1
    printf("%d\n", validateInput("Hello, World!", "[A-Za-z, ]+")); // 1
    printf("%d\n", validateInput("1234", "\\d{5}")); // 0
    printf("%d\n", validateInput("email@example.com", "[\\w.%+-]+@[\\w.-]+\\.[a-zA-Z]{2,6}")); // 1
    return 0;
}