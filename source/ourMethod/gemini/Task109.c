#include <stdio.h>
#include <stdbool.h>
#include <regex.h>

bool isValidInput(const char *input, const char *regex) {
    regex_t compiledRegex;
    int reti;

    reti = regcomp(&compiledRegex, regex, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&compiledRegex, input, 0, NULL, 0);
    regfree(&compiledRegex);

    if (!reti) {
        return true;
    } else if (reti == REG_NOMATCH) {
        return false;
    } else {
        char msgbuf[100];
        regerror(reti, &compiledRegex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return false;
    }
}

int main() {
    // Test cases
    printf("%d\n", isValidInput("abc123", "^[a-zA-Z0-9]+$")); // True - alphanumeric
    printf("%d\n", isValidInput("123.45", "^[0-9]+\\.[0-9]+$")); // True - floating-point number
    printf("%d\n", isValidInput("john.doe@example.com", "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$")); // True - email
    printf("%d\n", isValidInput("123-456-7890", "^[0-9]{3}-[0-9]{3}-[0-9]{4}$")); // True - phone number
    printf("%d\n", isValidInput("abc$", "^[a-zA-Z]+$")); // False - contains special character
    return 0;
}