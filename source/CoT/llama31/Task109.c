#include <regex.h>
#include <stdio.h>
#include <string.h>

bool validateInput(const char* input) {
    regex_t regex;
    int reti;
    char* pattern = "^[a-zA-Z0-9_.]+$";

    // Compile regular expression
    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    // Execute regular expression
    reti = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    if (!reti) {
        return true;
    } else if (reti == REG_NOMATCH) {
        return false;
    } else {
        fprintf(stderr, "Regex match failed\n");
        return false;
    }
}

int main() {
    char* testCases[] = {"abc123", "abc.123", "abc_123", "abc@123", "!abc123"};
    for (int i = 0; i < 5; ++i) {
        printf("Input: %s, Valid: %s\n", testCases[i], validateInput(testCases[i]) ? "true" : "false");
    }
    return 0;
}