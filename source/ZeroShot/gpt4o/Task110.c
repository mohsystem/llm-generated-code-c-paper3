#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

bool isValidURL(const char* url) {
    regex_t regex;
    int ret;
    const char* pattern = "^(https?|ftp)://[^\\s/$.?#].[^\\s]*$";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret) {
        return false;
    }
    
    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return !ret;
}

int main() {
    printf("%d\n", isValidURL("http://example.com")); // 1
    printf("%d\n", isValidURL("https://www.example.com/path/to/resource")); // 1
    printf("%d\n", isValidURL("ftp://example.com/file.txt")); // 1
    printf("%d\n", isValidURL("htt://wrongprotocol.com")); // 0
    printf("%d\n", isValidURL("http://invalid-url")); // 0
    return 0;
}