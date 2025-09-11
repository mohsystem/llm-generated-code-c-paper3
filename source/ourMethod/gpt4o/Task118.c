#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateIPAddress(const char *ipAddress) {
    int num, dots = 0;
    const char *ptr;
    if (ipAddress == NULL)
        return 0;
    ptr = ipAddress;

    while (*ptr) {
        if (*ptr == '.') {
            dots++;
        } else if (*ptr < '0' || *ptr > '9') {
            return 0;
        }
        ptr++;
    }

    if (dots != 3)
        return 0;

    ptr = strtok((char *)ipAddress, ".");
    while (ptr) {
        if (!isdigit(*ptr))
            return 0;

        num = atoi(ptr);
        if (num < 0 || num > 255)
            return 0;

        ptr = strtok(NULL, ".");
    }
    return 1;
}

int main() {
    printf("%d\n", validateIPAddress("192.168.1.1")); // true
    printf("%d\n", validateIPAddress("255.255.255.255")); // true
    printf("%d\n", validateIPAddress("256.256.256.256")); // false
    printf("%d\n", validateIPAddress("123.045.067.089")); // false
    printf("%d\n", validateIPAddress("192.168.1")); // false
    return 0;
}