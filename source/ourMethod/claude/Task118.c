
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_IP_LEN 16
#define OCTET_COUNT 4

bool validateIPAddress(const char* ipAddress) {
    if (ipAddress == NULL || strlen(ipAddress) == 0 || 
        strlen(ipAddress) >= MAX_IP_LEN) {
        return false;
    }
    
    char ipCopy[MAX_IP_LEN];
    strncpy(ipCopy, ipAddress, MAX_IP_LEN - 1);
    ipCopy[MAX_IP_LEN - 1] = '\\0';
    
    char* token = strtok(ipCopy, ".");
    int count = 0;
    
    while (token != NULL && count < OCTET_COUNT) {
        // Check for empty octets
        if (strlen(token) == 0 || strlen(token) > 3) {
            return false;
        }
        
        // Check for leading zeros
        if (strlen(token) > 1 && token[0] == '0') {
            return false;
        }
        
        // Check for non-numeric characters
        for (int i = 0; token[i] != '\\0'; i++) {
            if (token[i] < '0' || token[i] > '9') {
                return false;
            }
        }
        
        // Parse and validate range
        int value = atoi(token);
        if (value < 0 || value > 255) {
            return false;
        }
        
        count++;
        token = strtok(NULL, ".");
    }
    
    // Check if exactly 4 octets
    return count == OCTET_COUNT && token == NULL;
}

int main() {
    // Test cases
    const char* testIPs[] = {
        "192.168.1.1",     // valid
        "256.1.2.3",       // invalid - first octet > 255
        "1.2.3.4.5",       // invalid - too many octets
        "192.168.001.1",   // invalid - leading zeros
        "192.168.1.1."     // invalid - trailing dot
    };
    
    const int testCount = sizeof(testIPs) / sizeof(testIPs[0]);
    
    for (int i = 0; i < testCount; i++) {
        printf("IP: %s is %s\\n", testIPs[i], 
               validateIPAddress(testIPs[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
