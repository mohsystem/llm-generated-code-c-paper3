#include <stdio.h>
#include <regex.h>

bool is_valid_email(const char* email) {
    regex_t regex;
    const char* pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,6}$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) return false;
    int status = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    return status == 0;
}

int main() {
    const char* testCases[] = {"ankitrai326@gmail.com", "my.ownsite@our-earth.org", "ankitrai326.com", "invalid-email", "test@example.co.uk"};
    for (int i = 0; i < 5; i++) {
        if (is_valid_email(testCases[i])) {
            printf("%s is a valid email\n", testCases[i]);
        } else {
            printf("%s is not a valid email\n", testCases[i]);
        }
    }
    return 0;
}