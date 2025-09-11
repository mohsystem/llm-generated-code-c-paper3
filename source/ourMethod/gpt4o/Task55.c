#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidEmail(const char* email) {
    if (email == NULL) return 0;
    regex_t regex;
    const char* emailRegex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    if (regcomp(&regex, emailRegex, REG_EXTENDED) != 0) return 0;
    int result = regexec(&regex, email, 0, NULL, 0) == 0;
    regfree(&regex);
    return result;
}

int main() {
    // Test cases
    printf("%d\n", isValidEmail("test@example.com"));  // 1
    printf("%d\n", isValidEmail("invalid-email"));     // 0
    printf("%d\n", isValidEmail("user@.com"));         // 0
    printf("%d\n", isValidEmail("user@domain.co.uk")); // 1
    printf("%d\n", isValidEmail("user@domain"));       // 0
    return 0;
}