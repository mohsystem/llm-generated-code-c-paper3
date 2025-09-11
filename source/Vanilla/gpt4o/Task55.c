#include <stdio.h>
#include <stdbool.h>
#include <regex.h>

bool isValidEmail(const char *email) {
    regex_t regex;
    const char *pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$";
    regcomp(&regex, pattern, REG_EXTENDED);
    int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return result == 0;
}

int main() {
    printf("%d\n", isValidEmail("test@example.com")); // 1
    printf("%d\n", isValidEmail("user@domain.co.in")); // 1
    printf("%d\n", isValidEmail("username@.com")); // 0
    printf("%d\n", isValidEmail("username@domaincom")); // 0
    printf("%d\n", isValidEmail("user.name@domain.com")); // 1
    return 0;
}