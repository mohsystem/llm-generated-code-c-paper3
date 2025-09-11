#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

bool isValidURL(const char* url) {
    const char* urlPattern = "^(https?|ftp)://[a-zA-Z0-9.-]+(:[0-9]+)?(/.*)?$";
    regex_t regex;
    if (regcomp(&regex, urlPattern, REG_EXTENDED) != 0) {
        return false; // Failed to compile regex
    }
    int match = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return match == 0;
}

int main() {
    // Test cases
    printf("%d\n", isValidURL("http://example.com")); // 1 (true)
    printf("%d\n", isValidURL("https://example.com")); // 1 (true)
    printf("%d\n", isValidURL("ftp://example.com")); // 1 (true)
    printf("%d\n", isValidURL("http://example.com:8080")); // 1 (true)
    printf("%d\n", isValidURL("http://example.com/path/to/resource")); // 1 (true)
    return 0;
}