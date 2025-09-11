#include <stdio.h>
#include <stdbool.h>
#include <regex.h>

bool isValidURL(const char* url) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^(https?|ftp)://[^\\s/$.?#].[^\\s]*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

int main() {
    printf("%s\n", isValidURL("https://www.example.com") ? "true" : "false");
    printf("%s\n", isValidURL("http://example.com") ? "true" : "false");
    printf("%s\n", isValidURL("ftp://ftp.example.com") ? "true" : "false");
    printf("%s\n", isValidURL("invalid-url") ? "true" : "false");
    printf("%s\n", isValidURL("https://www.example.com/path?query=string#fragment") ? "true" : "false");
    return 0;
}