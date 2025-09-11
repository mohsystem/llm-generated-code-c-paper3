#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidEmail(const char *email) {
    if (email == NULL || strlen(email) == 0) {
        return 0;
    }
    regex_t regex;
    const char *emailRegex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    if (regcomp(&regex, emailRegex, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }
    int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return result == 0;
}

int main() {
    printf("%d\n", isValidEmail("test@example.com"));  // 1
    printf("%d\n", isValidEmail("invalid-email"));     // 0
    printf("%d\n", isValidEmail("another@test.co"));   // 1
    printf("%d\n", isValidEmail("bad@domain"));        // 0
    printf("%d\n", isValidEmail("good123@domain.org"));// 1
    return 0;
}