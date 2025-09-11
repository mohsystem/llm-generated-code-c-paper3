
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 2048

bool validateURL(const char* urlStr) {
    if (urlStr == NULL || strlen(urlStr) == 0) {
        return false;
    }
    
    // Check length to prevent DoS
    if (strlen(urlStr) > MAX_URL_LENGTH) {
        return false;
    }
    
    // Check if starts with http:// or https://
    bool hasScheme = false;
    const char* ptr = urlStr;
    
    if (strncmp(ptr, "http://", 7) == 0) {
        ptr += 7;
        hasScheme = true;
    } else if (strncmp(ptr, "https://", 8) == 0) {
        ptr += 8;
        hasScheme = true;
    }
    
    // Must have at least one character before dot
    bool hasDot = false;
    bool hasHost = false;
    
    while (*ptr) {
        if (*ptr == '.') {
            if (!hasHost || ptr[1] == '\\0') {
                return false;
            }
            hasDot = true;
        } else if (*ptr == '/') {
            break;
        } else if (!isalnum(*ptr) && *ptr != '-') {
            return false;
        } else {
            hasHost = true;
        }
        ptr++;
    }
    
    // Must have at least one dot and valid TLD
    if (!hasDot) {
        return false;
    }
    
    return true;
}

int main() {
    // Test cases
    const char* testUrls[] = {
        "https://www.example.com",
        "http://subdomain.example.co.uk/path?param=value",
        "invalid.url",
        "https://malicious<script>alert(1)</script>.com",
        "https://example.com/path?valid=true"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("URL: %s is %s\\n", testUrls[i], 
               validateURL(testUrls[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
