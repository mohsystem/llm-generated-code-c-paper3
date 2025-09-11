
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

bool validate_email(const char* email) {
    if (email == NULL || strlen(email) == 0) {
        return false;
    }
    
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$", REG_EXTENDED);
    if (ret) {
        return false;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

bool validate_phone(const char* phone) {
    if (phone == NULL || strlen(phone) == 0) {
        return false;
    }
    
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, "^[0-9]{10}$", REG_EXTENDED);
    if (ret) {
        return false;
    }
    
    ret = regexec(&regex, phone, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

bool validate_username(const char* username) {
    if (username == NULL || strlen(username) == 0) {
        return false;
    }
    
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, "^[A-Za-z0-9_]{3,20}$", REG_EXTENDED);
    if (ret) {
        return false;
    }
    
    ret = regexec(&regex, username, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main() {
    // Test cases
    const char* emails[] = {
        "test@example.com",
        "invalid.email@",
        "test.email@domain.com",
        "@invalid.com",
        "test@.com"
    };
    
    const char* phones[] = {
        "1234567890",
        "123456",
        "12345678901", 
        "abcdefghij",
        "123-456-7890"
    };
    
    const char* usernames[] = {
        "user123",
        "ab",
        "validUsername_123",
        "too_long_username_123456",
        "invalid@username"
    };

    // Test email validation
    printf("Email Validation:\\n");
    for (int i = 0; i < 5; i++) {
        printf("%s : %s\\n", emails[i], validate_email(emails[i]) ? "true" : "false");
    }

    // Test phone validation
    printf("\\nPhone Validation:\\n");
    for (int i = 0; i < 5; i++) {
        printf("%s : %s\\n", phones[i], validate_phone(phones[i]) ? "true" : "false");
    }

    // Test username validation
    printf("\\nUsername Validation:\\n");
    for (int i = 0; i < 5; i++) {
        printf("%s : %s\\n", usernames[i], validate_username(usernames[i]) ? "true" : "false");
    }

    return 0;
}
