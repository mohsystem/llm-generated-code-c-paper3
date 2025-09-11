#include <stdio.h>
#include <regex.h>

bool validateEmail(const char* email) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}$", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    // Execute regular expression
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    if (!reti) {
        return true;
    } else {
        return false;
    }
}

int main() {
    const char* testCases[] = {"john.doe@example.com", "john.doe@example", "john doe@example.com", "john.doe@.com", "john.doe@example.com.au"};
    for (int i = 0; i < 5; ++i) {
        printf("%s: %d\n", testCases[i], validateEmail(testCases[i]));
    }
    return 0;
}