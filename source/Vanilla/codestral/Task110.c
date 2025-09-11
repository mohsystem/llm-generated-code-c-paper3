#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

bool isValidUrl(const char *url) {
    regex_t regex;
    int ret;
    const char *pattern = "^(?:http|ftp)s?://"  // http:// or https://
                          "(?:(?:[A-Z0-9](?:[A-Z0-9-]{0,61}[A-Z0-9])?\\.)+(?:[A-Z]{2,6}\\.?|[A-Z0-9-]{2,}\\.?)|"  // domain...
                          "localhost|"  // localhost...
                          "\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})"  // ...or ip
                          "(:\\d+)?"  // optional port
                          "(/?|[/?]\\S+)$";

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        return true;
    } else if (ret == REG_NOMATCH) {
        return false;
    } else {
        char msgbuf[100];
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return false;
    }
}

int main() {
    printf("%d\n", isValidUrl("http://www.google.com"));  // 1
    printf("%d\n", isValidUrl("https://github.com/user"));  // 1
    printf("%d\n", isValidUrl("ftp://example.com"));  // 1
    printf("%d\n", isValidUrl("invalid url"));  // 0
    printf("%d\n", isValidUrl("http://invalid..com"));  // 0
    return 0;
}