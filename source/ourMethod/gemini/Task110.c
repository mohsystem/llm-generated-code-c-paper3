#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include <string.h>

bool isValidURL(const char* url) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^(?:http(s)?:\\/\\/)?[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:/?#[\\]@!\\$&'(\\)\\*\\+,;=.]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

int main() {
    char* testCases[] = {
        "https://www.example.com",
        "http://example.com",
        "ftp://ftp.example.com",
        "invalid-url",
        "https://www.example.com/path?query=string#fragment"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        printf("%s: %s\n", testCases[i], isValidURL(testCases[i]) ? "true" : "false");
    }

    return 0;
}