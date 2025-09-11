
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048
#define MALICIOUS_CHARS_COUNT 11

bool containsMaliciousChars(const char* url) {
    const char* maliciousChars[] = {"<", ">", "'", "\\"", ";", "(", ")", "{", "}", "|", "\\\\"};\n    \n    for (int i = 0; i < MALICIOUS_CHARS_COUNT; i++) {\n        if (strstr(url, maliciousChars[i]) != NULL) {\n            return true;\n        }\n    }\n    return false;\n}\n\nbool isValidURL(const char* urlStr) {\n    if (urlStr == NULL || strlen(urlStr) == 0 || strlen(urlStr) > MAX_URL_LENGTH) {\n        return false;\n    }\n\n    // Check for malicious characters\n    if (containsMaliciousChars(urlStr)) {\n        return false;\n    }\n\n    // Check URL format using regex\n    regex_t regex;\n    const char* pattern = "^(https?://)?([[:alnum:].-]+)\\\\.[[:alpha:]]{2,}(:[0-9]{2,5})?(/[[:alnum:]./?=#&-]*)?$";\n    \n    int reti = regcomp(&regex, pattern, REG_EXTENDED);\n    if (reti) {\n        return false;\n    }\n\n    reti = regexec(&regex, urlStr, 0, NULL, 0);\n    regfree(&regex);\n\n    if (reti) {\n        return false;\n    }\n\n    // Additional protocol check\n    const char* protocolStr = strstr(urlStr, "://");\n    if (protocolStr != NULL) {\n        char protocol[10] = {0};\n        size_t protocolLen = protocolStr - urlStr;\n        if (protocolLen >= sizeof(protocol)) {\n            return false;\n        }\n        strncpy(protocol, urlStr, protocolLen);\n        \n        if (strcmp(protocol, "http") != 0 && strcmp(protocol, "https") != 0) {\n            return false;\n        }\n    }\n\n    return true;\n}\n\nint main() {\n    // Test cases\n    const char* testUrls[] = {\n        "https://www.example.com",\n        "http://subdomain.example.co.uk/path?param=value",\n        "ftp://invalid.com", // Invalid protocol\n        "https://invalid<>.com", // Contains malicious chars\n        "not_a_url",\n        "https://example.com:8080/path"\n    };\n\n    for (int i = 0; i < 6; i++) {\n        printf("URL: %s is %s\
", testUrls[i], isValidURL(testUrls[i]) ? "valid" : "invalid");
    }

    return 0;
}
