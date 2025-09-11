#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include <string.h>

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
    printf("%d\n", isValidURL("https://www.example.com")); // 1
    printf("%d\n", isValidURL("http://example.com")); // 1
    printf("%d\n", isValidURL("ftp://ftp.example.com")); // 1
    printf("%d\n", isValidURL("example.com")); // 0
    printf("%d\n", isValidURL("htt://example.com")); // 0

    return 0;
}