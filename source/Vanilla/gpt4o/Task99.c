#include <stdio.h>
#include <regex.h>
#include <stdbool.h>

bool matchLine(const char* line) {
    regex_t regex;
    int reti;
    bool result = false;

    reti = regcomp(&regex, "^[0-9].*\\.$", REG_EXTENDED);
    if (reti) return false;

    reti = regexec(&regex, line, 0, NULL, 0);
    if (!reti) {
        result = true;
    } else if (reti == REG_NOMATCH) {
        result = false;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char* testCases[] = {
        "1. This is a test line.",
        "No number at start.",
        "2 Another line.",
        "3. Line with number at start and dot at end.",
        "No dot at end 4"
    };

    for (int i = 0; i < 5; ++i) {
        printf("%s -> %d\n", testCases[i], matchLine(testCases[i]));
    }

    return 0;
}