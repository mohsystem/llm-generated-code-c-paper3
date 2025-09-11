
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_EMAIL_LENGTH 254
#define MAX_LOCAL_LENGTH 64
#define MAX_DOMAIN_LENGTH 255

bool validateEmail(const char* email) {
    // Check for null/empty
    if (email == NULL || strlen(email) == 0) {
        return false;
    }
    
    // Check maximum length
    size_t len = strlen(email);
    if (len > MAX_EMAIL_LENGTH) {
        return false;
    }
    
    // Find @ symbol
    const char* at = strchr(email, '@');
    if (at == NULL || at == email || at == email + len - 1) {
        return false;
    }
    
    // Check local part and domain lengths
    size_t localLen = at - email;
    size_t domainLen = len - localLen - 1;
    
    if (localLen > MAX_LOCAL_LENGTH || domainLen > MAX_DOMAIN_LENGTH) {
        return false;
    }
    
    // Check for consecutive dots
    for (size_t i = 0; i < len - 1; i++) {
        if (email[i] == '.' && email[i+1] == '.') {
            return false;
        }
    }
    
    // Check for valid characters
    for (size_t i = 0; i < len; i++) {
        char c = email[i];
        if (!isalnum(c) && c != '@' && c != '.' && c != '-' && c != '_' && c != '+') {
            return false;
        }
    }
    
    return true;
}

int main() {
    // Test cases
    const char* testEmails[] = {
        "test@example.com",            // valid
        "user.name@domain.com",        // valid
        "invalid.email@",              // invalid
        "@invalid.com",                // invalid
        "test..email@domain.com"       // invalid
    };
    
    const int numTests = sizeof(testEmails) / sizeof(testEmails[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("Email: %s is %s\\n", 
               testEmails[i], 
               validateEmail(testEmails[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
