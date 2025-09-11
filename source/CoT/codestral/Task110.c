#include <regex.h>
#include <stdio.h>

int is_valid_url(const char* url) {
    regex_t regex;
    int reti = regcomp(&regex, "^(https?|ftp|file)://[\\w-]+(\\.[\\w-]+)+(/[\\w.-]*)*(\\?[\\w.-]+=\\w*)?$", REG_EXTENDED);
    if (reti) {
        printf("Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (!reti)
        return 1; // true
    else if (reti == REG_NOMATCH)
        return 0; // false
    else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        printf("Regex match failed: %s\n", msgbuf);
        return 0;
    }
}

int main() {
    printf("%d\n", is_valid_url("http://www.google.com")); // 1 (true)
    printf("%d\n", is_valid_url("https://stackoverflow.com/questions/163360/regular-expression-to-match-urls-in-java")); // 1 (true)
    printf("%d\n", is_valid_url("ftp://ftp.example.com/")); // 1 (true)
    printf("%d\n", is_valid_url("file:///C:/path/to/file.txt")); // 1 (true)
    printf("%d\n", is_valid_url("invalid-url")); // 0 (false)
    return 0;
}