#include <stdio.h>
#include <regex.h>

bool isValidURL(const char* url) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    const char* pattern = "((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    // Execute regular expression
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
    const char* testCases[] = {
        "https://www.geeksforgeeks.org",
        "http://www.google.com",
        "https:// www.geeksforgeeks.org/", // Invalid due to space
        "http:/www.google.com", // Invalid due to missing '/'
        "https://example.com"
    };

    for (int i = 0; i < 5; ++i) {
        if (isValidURL(testCases[i])) {
            printf("%s is valid\n", testCases[i]);
        } else {
            printf("%s is invalid\n", testCases[i]);
        }
    }

    return 0;
}