#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

bool isValidIP(const char *ip) {
    if (ip == NULL || strlen(ip) == 0) {
        return false;
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    /* Compile regular expression */
    reti = regcomp(&regex, "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    /* Execute regular expression */
    reti = regexec(&regex, ip, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        return true;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        return false;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        return false;
    }
}


int main() {
    printf("%d\n", isValidIP("0.0.0.0")); // 1 (true)
    printf("%d\n", isValidIP("255.255.255.255")); // 1 (true)
    printf("%d\n", isValidIP("192.168.1.1")); // 1 (true)
    printf("%d\n", isValidIP("256.256.256.256")); // 0 (false)
    printf("%d\n", isValidIP("192.168.1.256")); // 0 (false)
    return 0;
}