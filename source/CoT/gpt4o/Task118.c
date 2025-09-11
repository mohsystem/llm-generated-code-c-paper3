#include <stdio.h>
#include <regex.h>

int isValidIPAddress(const char *ipAddress) {
    const char *ipv4Pattern =
        "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";
    const char *ipv6Pattern =
        "([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|"
        "([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}"
        "(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4})"
        "{1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}"
        ":){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4})"
        "{1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}"
        "%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|2[0-4][0-9]|"
        "[01]?[0-9][0-9]?)\\.){3,3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)|"
        "([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.)"
        "{3,3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";

    regex_t regexIPv4, regexIPv6;
    int ret;

    ret = regcomp(&regexIPv4, ipv4Pattern, REG_EXTENDED);
    if (ret) return 0;
    ret = regcomp(&regexIPv6, ipv6Pattern, REG_EXTENDED);
    if (ret) return 0;

    ret = regexec(&regexIPv4, ipAddress, 0, NULL, 0);
    if (!ret) return 1;
    ret = regexec(&regexIPv6, ipAddress, 0, NULL, 0);
    if (!ret) return 1;

    regfree(&regexIPv4);
    regfree(&regexIPv6);

    return 0;
}

int main() {
    const char* testCases[] = {
        "192.168.1.1",    // valid IPv4
        "255.255.255.255", // valid IPv4
        "0.0.0.0",        // valid IPv4
        "256.256.256.256", // invalid IPv4
        "2001:0db8:85a3:0000:0000:8a2e:0370:7334" // valid IPv6
    };

    for (int i = 0; i < 5; i++) {
        printf("%s is valid: %s\n", testCases[i], isValidIPAddress(testCases[i]) ? "true" : "false");
    }

    return 0;
}