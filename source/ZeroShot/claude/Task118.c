
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_IP_LENGTH 16

bool isValidIP(const char* ipAddress) {
    if (ipAddress == NULL || strlen(ipAddress) == 0) {
        return false;
    }
    
    char ip_copy[MAX_IP_LENGTH];
    strncpy(ip_copy, ipAddress, MAX_IP_LENGTH - 1);
    ip_copy[MAX_IP_LENGTH - 1] = '\\0';
    
    char* part = strtok(ip_copy, ".");
    int count = 0;
    
    while (part != NULL) {
        count++;
        if (count > 4) {
            return false;
        }
        
        int len = strlen(part);
        if (len == 0 || (len > 1 && part[0] == '0')) {
            return false;
        }
        
        char* endptr;
        long value = strtol(part, &endptr, 10);
        
        if (*endptr != '\\0' || value < 0 || value > 255) {
            return false;
        }
        
        part = strtok(NULL, ".");
    }
    
    return count == 4;
}

int main() {
    // Test cases
    const char* testIPs[] = {
        "192.168.1.1",
        "256.1.2.3",
        "1.1.1.1",
        "01.02.03.04",
        "192.168.001.1"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("%s is %s\\n", testIPs[i], isValidIP(testIPs[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
