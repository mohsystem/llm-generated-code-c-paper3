#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* validIPAddress(const char* IP) {
    if (strchr(IP, '.') != NULL) {
        return validateIPv4(IP);
    } else if (strchr(IP, ':') != NULL) {
        return validateIPv6(IP);
    } else {
        return "Neither";
    }
}

char* validateIPv4(const char* ip) {
    char* token = strtok((char*)ip, ".");
    int count = 0;

    while (token != NULL) {
        if (++count > 4) return "Neither";
        if (strlen(token) > 3 || (strlen(token) > 1 && token[0] == '0')) return "Neither";
        for (int i = 0; i < strlen(token); i++) {
            if (!isdigit(token[i])) return "Neither";
        }
        int num = atoi(token);
        if (num < 0 || num > 255) return "Neither";
        token = strtok(NULL, ".");
    }
    return "IPv4";
}

char* validateIPv6(const char* ip) {
    char* token = strtok((char*)ip, ":");
    int count = 0;

    while (token != NULL) {
        if (++count > 8) return "Neither";
        if (strlen(token) > 4) return "Neither";
        for (int i = 0; i < strlen(token); i++) {
            if (!((token[i] >= '0' && token[i] <= '9') || (token[i] >= 'a' && token[i] <= 'f') || (token[i] >= 'A' && token[i] <= 'F'))) return "Neither";
        }
        int num = strtol(token, NULL, 16);
        if (num < 0 || num > 65535) return "Neither";
        token = strtok(NULL, ":");
    }
    return "IPv6";
}

int main() {
    const char* testCases[] = {"192.168.1.1", "2001:0db8:85a3:0000:0000:8a2e:0370:7334", "256.1.1.1", "2001:0db8:85a3:0000:0000:8a2e:0370:733g"};
    for (int i = 0; i < 4; i++) {
        printf("%s\n", validIPAddress(testCases[i]));
    }
    return 0;
}