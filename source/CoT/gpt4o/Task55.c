#include <stdio.h>
#include <stdbool.h>
#include <regex.h>

bool isValidEmail(const char *email) {
    if (!email || email[0] == '\0') return false;
    
    // Regular expression to validate email
    const char *emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
    regex_t regex;
    int result = regcomp(&regex, emailRegex, REG_EXTENDED);
    if (result) return false;

    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return !result;
}

int main() {
    printf("%d\n", isValidEmail("test@example.com"));  // 1 (true)
    printf("%d\n", isValidEmail("user@domain.co.in"));  // 1 (true)
    printf("%d\n", isValidEmail("user.name@domain.com"));  // 1 (true)
    printf("%d\n", isValidEmail("user#domain.com"));  // 0 (false)
    printf("%d\n", isValidEmail("user@domaincom"));  // 0 (false)
    return 0;
}