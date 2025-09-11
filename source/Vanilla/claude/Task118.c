
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool validateIP(const char* ipAddress) {
    if (!ipAddress || strlen(ipAddress) == 0) {
        return false;
    }
    
    int values[4];
    int parts = 0;
    char ipCopy[16];
    strncpy(ipCopy, ipAddress, sizeof(ipCopy) - 1);
    ipCopy[sizeof(ipCopy) - 1] = '\\0';
    
    char* token = strtok(ipCopy, ".");
    while (token != NULL && parts < 4) {
        if (strlen(token) > 1 && token[0] == '0') {
            return false;
        }
        
        char* endptr;
        long value = strtol(token, &endptr, 10);
        
        if (*endptr != '\\0' || value < 0 || value > 255) {
            return false;
        }
        
        values[parts++] = value;
        token = strtok(NULL, ".");
    }
    
    return parts == 4 && token == NULL;
}

int main() {
    const char* testIPs[] = {
        "192.168.1.1",
        "256.1.2.3",
        "1.1.1.1",
        "01.02.03.04",
        "192.168.001.1"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("IP: %s is %s\\n", testIPs[i], validateIP(testIPs[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
