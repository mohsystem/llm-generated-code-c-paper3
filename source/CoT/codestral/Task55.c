#include <stdio.h>
#include <regex.h>
#include <stdbool.h>

bool isValidEmail(const char *email) {
    if (email == NULL) return false;
    regex_t regex;
    int ret = regcomp(&regex, "^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$", REG_EXTENDED);
    if (ret) return false;
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return ret == 0;
}

int main() {
    printf("%d\n", isValidEmail("test.email@example.com")); // 1 (true)
    printf("%d\n", isValidEmail("invalid.email")); // 0 (false)
    printf("%d\n", isValidEmail("test@sub.example.co")); // 1 (true)
    printf("%d\n", isValidEmail("test@sub@example.com")); // 0 (false)
    printf("%d\n", isValidEmail("test.email@example")); // 0 (false)
    return 0;
}