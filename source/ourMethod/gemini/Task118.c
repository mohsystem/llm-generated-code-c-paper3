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

    reti = regcomp(&regex, "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    reti = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

int main() {
    const char *testCases[] = {
        "192.168.1.1",
        "256.256.256.256",
        "10.0.0.1",
        "172.16.0.0",
        "2001:0db8:85a3:0000:0000:8a2e:0370:7334"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        bool isValid = isValidIP(testCases[i]);
        printf("%s: %s\n", testCases[i], isValid ? "true" : "false");
    }

    return 0;
}