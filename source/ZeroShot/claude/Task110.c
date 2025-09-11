
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validateURL(const char* url) {
    if (url == NULL || strlen(url) == 0) {
        return false;
    }
    
    // Basic URL validation (simplified due to C limitations)
    // Check for valid protocol
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) {
        return false;
    }
    
    // Check for minimum length
    if (strlen(url) < 10) {
        return false;
    }
    
    // Check for invalid characters
    for (int i = 0; url[i] != '\\0'; i++) {
        if (!isalnum(url[i]) && url[i] != '.' && url[i] != '-' && 
            url[i] != '/' && url[i] != ':' && url[i] != '_' && 
            url[i] != '?' && url[i] != '=' && url[i] != '&' && 
            url[i] != '@') {
            return false;
        }
    }
    
    // Check for at least one dot after protocol
    const char* dot = strchr(url + 8, '.');
    if (dot == NULL) {
        return false;
    }
    
    return true;
}

int main() {
    // Test cases
    const char* urls[] = {
        "https://www.example.com",
        "http://subdomain.example.co.uk/path?param=1",
        "invalid url",
        "ftp://invalid.com",
        "https://valid-url.com:8080/path"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("URL: %s is %s\\n", urls[i], validateURL(urls[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
