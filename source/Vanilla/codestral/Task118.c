#include <regex.h>
#include <stdio.h>

int isValidIP(const char *ip) {
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    ret = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);
    return !ret;
}

int main() {
    printf("%d\n", isValidIP("192.168.1.1"));  // 1 (true)
    printf("%d\n", isValidIP("256.168.1.1"));  // 0 (false)
    printf("%d\n", isValidIP("192.168.01.1")); // 0 (false)
    printf("%d\n", isValidIP("192.168.1.01")); // 0 (false)
    printf("%d\n", isValidIP("192.168.1"));     // 0 (false)
    return 0;
}