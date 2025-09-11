#include <stdio.h>
#include <regex.h>

bool isValidEmail(const char* email) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,6}$", REG_ICASE);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    // Execute regular expression
    reti = regexec(&regex, email, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        return true;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        return false;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        return false;
    }
}

int main() {
    const char* testCases[] = {"test@example.com", "invalid-email", "test@example", "test@.com", "test@example.com.au"};
    for (int i = 0; i < 5; ++i) {
        if (isValidEmail(testCases[i])) {
            printf("%s is a valid email.\n", testCases[i]);
        } else {
            printf("%s is not a valid email.\n", testCases[i]);
        }
    }
    return 0;
}