#include <stdio.h>
#include <string.h>
#include <regex.h>

int validateURL(const char *url) {
    regex_t regex;
    const char *pattern = "^((http|https|ftp):\\/\\/)?([\\w-]+(\\.[\\w-]+)+)([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?$";
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) return 0;
    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

int main() {
    printf("%d\n", validateURL("http://example.com")); // 1
    printf("%d\n", validateURL("https://example.com")); // 1
    printf("%d\n", validateURL("ftp://example.com")); // 1
    printf("%d\n", validateURL("invalid://example.com")); // 0
    printf("%d\n", validateURL("example.com")); // 0
    return 0;
}