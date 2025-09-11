#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidIP(const char *ip) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    /* Compile regular expression */
    reti = regcomp(&regex, "^(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    /* Execute regular expression */
    reti = regexec(&regex, ip, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        return 1;
    }
    else if (reti == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        return 0;
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