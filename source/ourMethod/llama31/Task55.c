#include <stdio.h>
#include <regex.h>

bool isValidEmail(const char* email) {
    const char* regex = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}$";
    regex_t re;
    if (regcomp(&re, regex, REG_EXTENDED) != 0) return false;
    int status = regexec(&re, email, 0, NULL, 0);
    regfree(&re);
    return status == 0;
}

int main() {
    const char* testCases[] = {
        "ankitrai326@gmail.com",
        "my.ownsite@our-earth.org",
        "ankitrai326.com",
        "invalid@email",
        "another@valid.email"
    };

    for (int i = 0; i < 5; ++i) {
        printf("%s : %s\n", testCases[i], isValidEmail(testCases[i]) ? "Valid" : "Invalid");
    }

    return 0;
}