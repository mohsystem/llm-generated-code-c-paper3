#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validate_ip(const char* ip) {
    char* token;
    char* rest = strdup(ip);
    int parts[4];
    int i = 0;
    while ((token = strtok_r(rest, ".", &rest))) {
        char* end;
        long val = strtol(token, &end, 10);
        if (*end != '\0' || val < 0 || val > 255) {
            return 0;
        }
        parts[i++] = val;
    }
    return i == 4;
}

int main() {
    const char* ips[] = {"192.168.0.1", "256.0.0.1", "192.168.0.abc", "192.168.0.1.2", "192.168.0.-1"};
    for (int i = 0; i < 5; i++) {
        printf("%s is valid: %d\n", ips[i], validate_ip(ips[i]));
    }
    return 0;
}