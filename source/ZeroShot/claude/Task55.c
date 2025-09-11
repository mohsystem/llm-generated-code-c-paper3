
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isValidEmail(const char* email) {
    if (!email || strlen(email) == 0) {
        return false;
    }
    
    // Find @ position
    const char* at = strchr(email, '@');
    if (!at || at == email || !*(at + 1)) {
        return false;
    }
    
    // Check local part
    for (const char* c = email; c < at; c++) {
        if (!isalnum(*c) && *c != '.' && *c != '_' && *c != '+' && *c != '&' && *c != '*' && *c != '-') {
            return false;
        }
    }
    
    // Check domain part
    bool foundDot = false;
    const char* lastDot = NULL;
    for (const char* c = at + 1; *c; c++) {
        if (*c == '.') {
            if (c == at + 1 || !*(c + 1)) {
                return false;
            }
            foundDot = true;
            lastDot = c;
        } else if (!isalnum(*c) && *c != '-') {
            return false;
        }
    }
    
    if (!foundDot || !lastDot) {
        return false;
    }
    
    // Check TLD length (2-7 characters)
    size_t tldLength = strlen(lastDot + 1);
    return tldLength >= 2 && tldLength <= 7;
}

int main() {
    const char* emails[] = {
        "test@example.com",
        "user.name@domain.co.in",
        "invalid.email@",
        "@invalid.com",
        "test@.com"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("%s is %s\\n", emails[i], isValidEmail(emails[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
