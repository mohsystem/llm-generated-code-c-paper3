#include <stdio.h>
#include <regex.h>

int is_valid_url(const char* url) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "(http|https|ftp)://[^\\s/$.?#].[^\\s]*", 0);
    if (reti) {
        printf("Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        printf("Regex match failed: %s\n", msgbuf);
        return 0;
    }
}

int main() {
    printf("%d\n", is_valid_url("https://www.google.com")); // 1
    printf("%d\n", is_valid_url("http://stackoverflow.com")); // 1
    printf("%d\n", is_valid_url("ftp://example.com")); // 1
    printf("%d\n", is_valid_url("www.google.com")); // 0, missing protocol
    printf("%d\n", is_valid_url("google.com")); // 0, missing protocol
    return 0;
}