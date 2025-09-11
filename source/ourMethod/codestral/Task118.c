#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

bool isValidIp(const char *ip) {
    regex_t regex;
    int reti = regcomp(&regex, "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }
    reti = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

int main() {
    const char *testCases[] = {"192.168.1.1", "256.0.0.0", "127.0.0.1", "192.168.0.", "192.168.0.1.1"};
    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        printf("%s is valid: %s\n", testCases[i], isValidIp(testCases[i]) ? "true" : "false");
    }
    return 0;
}