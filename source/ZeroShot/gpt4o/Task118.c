#include <stdio.h>
#include <stdbool.h>
#include <regex.h>

bool isValidIPAddress(const char *ip) {
    regex_t regex;
    const char *pattern =
        "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return false;
    }

    ret = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main() {
    printf("%d\n", isValidIPAddress("192.168.1.1"));     // true
    printf("%d\n", isValidIPAddress("255.255.255.255")); // true
    printf("%d\n", isValidIPAddress("256.256.256.256")); // false
    printf("%d\n", isValidIPAddress("192.168.1"));       // false
    printf("%d\n", isValidIPAddress("192.168.1.01"));    // true
    return 0;
}