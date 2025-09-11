#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isValidIP(char* ip) {
    char* part = strtok(ip, ".");
    int parts[4];
    int i = 0;
    while (part != NULL) {
        parts[i++] = atoi(part);
        part = strtok(NULL, ".");
    }
    if (i != 4) {
        return 0;
    }
    for (int j = 0; j < 4; j++) {
        if (parts[j] < 0 || parts[j] > 255) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char* testCases[] = {"192.168.1.1", "256.168.1.1", "192.168.1", "192.168.1.abc"};
    for (int i = 0; i < 4; i++) {
        printf("%s is valid: %d\n", testCases[i], isValidIP(testCases[i]));
    }
    return 0;
}