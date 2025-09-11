#include <stdio.h>
#include <regex.h>

int validateURL(const char* url) {
    regex_t regex;
    int result;
    const char* pattern = "^((https?|ftp)://[^\\s/$.?#].[^\\s]*)$";
    regcomp(&regex, pattern, REG_EXTENDED);
    result = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return !result;
}

int main() {
    printf("%d\n", validateURL("http://example.com")); // 1
    printf("%d\n", validateURL("https://www.example.com/test")); // 1
    printf("%d\n", validateURL("ftp://example.com/resource")); // 1
    printf("%d\n", validateURL("htp://example.com")); // 0
    printf("%d\n", validateURL("http://.com")); // 0
    return 0;
}