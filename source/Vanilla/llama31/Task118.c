#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isIPv4Segment(const char* segment) {
    int val = atoi(segment);
    return val >= 0 && val <= 255 && (strlen(segment) == 1 || segment[0] != '0');
}

bool isIPv6Segment(const char* segment) {
    if (strlen(segment) > 4) return false;
    for (int i = 0; i < strlen(segment); i++) {
        char c = segment[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))) return false;
    }
    return true;
}

char* validIPAddress(const char* IP) {
    static char result[10];
    if (strchr(IP, '.') != NULL) {
        const char* start = IP;
        int count = 0;
        while (true) {
            const char* end = strchr(start, '.');
            if (end == NULL) end = IP + strlen(IP);
            char segment[10];
            strncpy(segment, start, end - start);
            segment[end - start] = '\0';
            if (!isIPv4Segment(segment)) return strcpy(result, "Neither");
            count++;
            if (*end == '\0') break;
            start = end + 1;
        }
        if (count != 4) return strcpy(result, "Neither");
        return strcpy(result, "IPv4");
    } else if (strchr(IP, ':') != NULL) {
        const char* start = IP;
        int count = 0;
        while (true) {
            const char* end = strchr(start, ':');
            if (end == NULL) end = IP + strlen(IP);
            char segment[10];
            strncpy(segment, start, end - start);
            segment[end - start] = '\0';
            if (!isIPv6Segment(segment)) return strcpy(result, "Neither");
            count++;
            if (*end == '\0') break;
            start = end + 1;
        }
        if (count != 8) return strcpy(result, "Neither");
        return strcpy(result, "IPv6");
    } else {
        return strcpy(result, "Neither");
    }
}

int main() {
    printf("%s\n", validIPAddress("192.168.1.1"));  // IPv4
    printf("%s\n", validIPAddress("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));  // IPv6
    printf("%s\n", validIPAddress("256.1.1.1"));  // Neither
    printf("%s\n", validIPAddress("2001:0db8:85a3:0000:0000:8a2e:0370:73345"));  // Neither
    printf("%s\n", validIPAddress("192.168.1"));  // Neither
    return 0;
}