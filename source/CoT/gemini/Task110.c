#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include <string.h>

bool isValidURL(const char* url) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Basic URL pattern check (improve as needed)
    reti = regcomp(&regex, "^(https?|ftp)://[^\\s/$.?#].[^\\s]*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
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
    char* testUrls[] = {
            "https://www.example.com",
            "http://example.com",
            "ftp://ftp.example.com",
            "invalid-url",
            "https://www.example.com/path?query=string#fragment"
    };
    int numUrls = sizeof(testUrls) / sizeof(testUrls[0]);

    for (int i = 0; i < numUrls; i++) {
        printf("%s: %s\n", testUrls[i], isValidURL(testUrls[i]) ? "true" : "false");
    }

    return 0;
}