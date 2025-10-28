
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 2048

bool is_valid_scheme(const char* scheme) {
    char lower_scheme[10];
    int i = 0;
    while (scheme[i] && i < 9) {
        lower_scheme[i] = tolower(scheme[i]);
        i++;
    }
    lower_scheme[i] = '\0';
    
    return strcmp(lower_scheme, "http") == 0 || 
           strcmp(lower_scheme, "https") == 0 || 
           strcmp(lower_scheme, "ftp") == 0;
}

bool is_valid_host_char(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= '0' && c <= '9') || 
           c == '.' || c == '-';
}

bool is_valid_host(const char* host) {
    if (!host || strlen(host) == 0) {
        return false;
    }
    
    int len = strlen(host);
    for (int i = 0; i < len; i++) {
        if (!is_valid_host_char(host[i])) {
            return false;
        }
    }
    
    if (host[0] == '-' || host[len-1] == '-' || host[0] == '.' || host[len-1] == '.') {
        return false;
    }
    
    return true;
}

bool validate_url(const char* url) {
    if (!url || strlen(url) == 0) {
        return false;
    }
    
    int len = strlen(url);
    if (len > MAX_URL_LENGTH) {
        return false;
    }
    
    for (int i = 0; i < len; i++) {
        if (url[i] == ' ' || url[i] == '\n' || url[i] == '\r' || url[i] == '\t') {
            return false;
        }
    }
    
    char scheme[10] = {0};
    char host[256] = {0};
    int scheme_idx = 0;
    int i = 0;
    
    while (url[i] && url[i] != ':' && scheme_idx < 9) {
        scheme[scheme_idx++] = url[i++];
    }
    scheme[scheme_idx] = '\0';
    
    if (!is_valid_scheme(scheme)) {
        return false;
    }
    
    if (url[i] != ':' || url[i+1] != '/' || url[i+2] != '/') {
        return false;
    }
    i += 3;
    
    int host_idx = 0;
    while (url[i] && url[i] != '/' && url[i] != ':' && url[i] != '?' && url[i] != '#' && host_idx < 255) {
        host[host_idx++] = url[i++];
    }
    host[host_idx] = '\0';
    
    if (!is_valid_host(host)) {
        return false;
    }
    
    if (url[i] == ':') {
        i++;
        int port = 0;
        while (url[i] >= '0' && url[i] <= '9') {
            port = port * 10 + (url[i] - '0');
            i++;
        }
        if (port < 1 || port > 65535) {
            return false;
        }
    }
    
    while (url[i]) {
        if (url[i] == '.' && url[i+1] == '.') {
            return false;
        }
        if (url[i] == '/' && url[i+1] == '/') {
            return false;
        }
        if (url[i] == '\\') {
            return false;
        }
        if (url[i] == '@') {
            return false;
        }
        i++;
    }

    return true;
}

int main() {
    const char* test_cases[] = {
        "https://www.example.com",
        "http://192.168.1.1:8080/path/to/resource",
        "ftp://files.example.org/downloads",
        "javascript:alert('XSS')",
        "https://example.com/path/../../../etc/passwd"
    };

    printf("URL Validation Results:\n");
    for (int i = 0; i < 5; i++) {
        bool is_valid = validate_url(test_cases[i]);
        printf("Test %d: %s\n", i + 1, test_cases[i]);
        printf("Valid: %s\n\n", is_valid ? "true" : "false");
    }
}
