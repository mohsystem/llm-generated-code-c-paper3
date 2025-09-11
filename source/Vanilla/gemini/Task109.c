#include <stdio.h>
#include <regex.h>
#include <string.h>

int isValidInput(const char* input) {
    // Example: Validate email format
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[A-Za-z0-9+_.-]+@(.+)$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return -1; // Indicate error
    }

    reti = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1; // Match found (true)
    } else if (reti == REG_NOMATCH) {
        return 0; // No match (false)
    } else {
        fprintf(stderr, "Regex match failed\n");
        return -1; // Indicate error
    }
}

int main() {
    printf("%d\n", isValidInput("test@example.com")); // 1 (true)
    printf("%d\n", isValidInput("invalid_email")); // 0 (false)
    printf("%d\n", isValidInput("another.test@subdomain.example.com")); // 1 (true)
    printf("%d\n", isValidInput("123@456.789")); // 1 (true)
    printf("%d\n", isValidInput("test@@example.com")); // 0 (false)
    return 0;
}