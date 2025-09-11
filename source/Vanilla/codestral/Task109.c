#include <regex.h>
#include <stdio.h>
#include <stdbool.h>

bool validateInput(const char* input) {
    regex_t regex;
    int reti = regcomp(&regex, "[a-zA-Z0-9]{6,}", 0);  // At least 6 alphanumeric characters
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

int main() {
    const char* testCases[] = {"Abc123", "abc", "abc123def", "abc!@#", "123456"};
    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        printf("%s: %s\n", testCases[i], validateInput(testCases[i]) ? "true" : "false");
    }
    return 0;
}