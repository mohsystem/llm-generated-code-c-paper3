#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

bool validateURL(const char* urlString) {
    regex_t regex;
    const char* pattern = "((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)";
    int reti = regcomp(&regex, pattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, urlString, 0, NULL, 0);
    regfree(&regex);
    return reti == 0;
}

int main() {
    const char* testCases[] = {"https://www.geeksforgeeks.org", "http://example.com", "invalid url", "https://www.example.com/path?query=param", "ftp://example.com"};
    for (int i = 0; i < 5; ++i) {
        printf("%s: %s\n", testCases[i], validateURL(testCases[i]) ? "true" : "false");
    }
    return 0;
}