#include <stdio.h>
#include <regex.h>

bool isValidURL(const char* url) {
    regex_t regex;
    const char* pattern = "^https?://[^/]+.*$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) return false;
    int match = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return match == 0;
}

int main() {
    const char* testCases[] = {
        "https://www.example.com",
        "http://www.example.com",
        "invalid-url",
        "ftp://example.com",
        "https://example.com/path?query=param"
    };

    for (int i = 0; i < 5; i++) {
        printf("%s is valid: %s\n", testCases[i], isValidURL(testCases[i]) ? "true" : "false");
    }

    return 0;
}