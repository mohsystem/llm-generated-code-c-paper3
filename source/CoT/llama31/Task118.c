#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* validIPAddress(char* IP) {
    if (strchr(IP, '.') != NULL) {
        return validateIPv4(IP);
    } else if (strchr(IP, ':') != NULL) {
        return validateIPv6(IP);
    } else {
        return "Neither";
    }
}

char* validateIPv4(char* ip) {
    char* token = strtok(ip, ".");
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
    if (count != 4) return "Neither";
    return "IPv4";
}

char* validateIPv6(char* ip) {
    char* token = strtok(ip, ":");
    int count = 0;
    while (token != NULL) {
        if (++count > 8) return "Neither";
        if (strlen(token) > 4 || strlen(token) < 1) return "Neither";
        for (int i = 0; i < strlen(token); i++) {
            char c = token[i];
            if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F')) return "Neither";
        }
        token = strtok(NULL, ":");
    }
    if (count != 8) return "Neither";
    return "IPv6";
}

int main() {
    char IP1[] = "192.168.1.1";
    char IP2[] = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    char IP3[] = "256.1.1.1";
    char IP4[] = "2001:0db8:85a3:0000:0000:8a2e:0370:733g";
    char IP5[] = "192.168.1";

    printf("%s\n", validIPAddress(IP1)); // IPv4
    printf("%s\n", validIPAddress(IP2)); // IPv6
    printf("%s\n", validIPAddress(IP3)); // Neither
    printf("%s\n", validIPAddress(IP4)); // Neither
    printf("%s\n", validIPAddress(IP5)); // Neither

    return 0;
}