
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidEmail(const char* email) {
    if (email == NULL || strlen(email) == 0)
        return false;
        
    // Check for @ and . symbols
    const char* atSign = strchr(email, '@');
    const char* lastDot = strrchr(email, '.');
    
    if (atSign == NULL || lastDot == NULL ||
        atSign == email || lastDot < atSign + 2 || *(lastDot + 1) == '\\0')
        return false;
        
    // Check for valid characters
    const char* allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-_@";
    for (const char* p = email; *p != '\\0'; p++) {
        if (strchr(allowedChars, *p) == NULL)
            return false;
    }
    
    return true;
}

int main() {
    // Test cases
    const char* emails[] = {
        "test@example.com",
        "invalid.email@com",
        "no@dot",
        "@nocontent.com",
        "test.email@domain.co.uk"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("%s is %s\\n", emails[i], isValidEmail(emails[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
