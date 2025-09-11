
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 254
#define MAX_LOCAL_LENGTH 64
#define MAX_DOMAIN_LENGTH 255

bool is_valid_char(char c) {
    return isalnum(c) || c == '.' || c == '_' || c == '-';
}

bool is_valid_domain_char(char c) {
    return isalnum(c) || c == '.' || c == '-';
}

bool is_valid_email(const char* email) {
    if (email == NULL || strlen(email) == 0) {
        return false;
    }
    
    // Check maximum length to prevent buffer overflow
    size_t len = strlen(email);
    if (len > MAX_EMAIL_LENGTH) {
        return false;
    }

    // Find @ symbol
    const char* at = strchr(email, '@');
    if (at == NULL || at == email || *(at + 1) == '\\0') {
        return false;
    }

    // Validate local part
    size_t local_len = at - email;
    if (local_len > MAX_LOCAL_LENGTH) {
        return false;
    }
    
    for (size_t i = 0; i < local_len; i++) {
        if (!is_valid_char(email[i])) {
            return false;
        }
    }

    // Validate domain part
    const char* domain = at + 1;
    size_t domain_len = strlen(domain);
    if (domain_len > MAX_DOMAIN_LENGTH) {
        return false;
    }

    // Must have at least one dot in domain
    bool has_dot = false;
    for (size_t i = 0; i < domain_len; i++) {
        if (!is_valid_domain_char(domain[i])) {
            return false;
        }
        if (domain[i] == '.') {
            has_dot = true;
        }
    }

    return has_dot;
}

int main() {
    // Test cases
    const char* test_emails[] = {
        "test@example.com",           // valid
        "user.name@domain.co.uk",     // valid
        "invalid.email@",             // invalid
        "@nodomain.com",              // invalid
        "no.at.symbol"                // invalid
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Email: %s is %s\\n", 
               test_emails[i], 
               is_valid_email(test_emails[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
