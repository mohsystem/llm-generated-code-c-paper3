#include <stdio.h>
#include <regex.h>

int validateIPAddress(const char* ipAddress) {
    regex_t regex;
    int result;
    const char* ipPattern =
        "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

    result = regcomp(&regex, ipPattern, REG_EXTENDED);
    if (result) {
        return 0;
    }

    result = regexec(&regex, ipAddress, 0, NULL, 0);
    regfree(&regex);

    return !result;
}

int main() {
    const char* testCases[] = {
        "192.168.1.1",
        "255.255.255.255",
        "256.256.256.256",
        "192.168.1",
        "abc.def.ghi.jkl"
    };

    for (int i = 0; i < 5; i++) {
        printf("%s is valid: %d\n", testCases[i], validateIPAddress(testCases[i]));
    }
    return 0;
}