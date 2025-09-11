#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidEmail(const char *email) {
    if (email == NULL || strlen(email) == 0) {
        return 0;
    }

    // Regular expression for email validation
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "^[A-Za-z0-9+_.-]+@(.+)$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }
}

int main() {
    char *testCases[] = {
        "test@example.com",
        "invalid-email",
        "another.test@sub.example.co.uk",
        "test@.com",
        "123@example"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        printf("%s: %d\n", testCases[i], isValidEmail(testCases[i]));
    }

    return 0;
}