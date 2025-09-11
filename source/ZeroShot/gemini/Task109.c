#include <stdio.h>
#include <string.h>
#include <regex.h>

int validateInput(const char *input, const char *regex) {
    regex_t compiled_regex;
    int reti;

    reti = regcomp(&compiled_regex, regex, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return -1; // Indicate an error
    }

    reti = regexec(&compiled_regex, input, 0, NULL, 0);
    regfree(&compiled_regex);

    if (!reti) {
        return 1; // Match found (true)
    } else if (reti == REG_NOMATCH) {
        return 0; // No match (false)
    } else {
        char msgbuf[100];
        regerror(reti, &compiled_regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return -1; // Indicate an error
    }
}

int main() {
    printf("%d\n", validateInput("abc123xyz", "^[a-z0-9]+$")); // 1 (true)
    printf("%d\n", validateInput("abc 123 xyz", "^[a-z0-9]+$")); // 0 (false)
    printf("%d\n", validateInput("123-456-7890", "^\\d{3}-\\d{3}-\\d{4}$")); // 1 (true)
    printf("%d\n", validateInput("john.doe@example.com", "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$")); // 1 (true)
    printf("%d\n", validateInput("password", "^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$")); // 0 (false)
    return 0;
}