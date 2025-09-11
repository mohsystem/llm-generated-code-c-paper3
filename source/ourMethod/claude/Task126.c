
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

char* redirectUser(const char* userInput) {
    // Input validation
    if(userInput == NULL || strlen(userInput) == 0 || strlen(userInput) >= MAX_INPUT) {
        return "/error.html";
    }
    
    // Sanitize input
    char sanitizedInput[MAX_INPUT] = {0};
    int j = 0;
    
    for(int i = 0; userInput[i] != '\\0' && j < MAX_INPUT-1; i++) {
        if(isalnum((unsigned char)userInput[i])) {
            sanitizedInput[j++] = tolower((unsigned char)userInput[i]);
        }
    }
    sanitizedInput[j] = '\\0';
    
    // Check against valid redirects
    if(strcmp(sanitizedInput, "home") == 0) {
        return "/home.html";
    }
    else if(strcmp(sanitizedInput, "about") == 0) {
        return "/about.html";
    }
    else if(strcmp(sanitizedInput, "contact") == 0) {
        return "/contact.html";
    }
    else if(strcmp(sanitizedInput, "products") == 0) {
        return "/products.html";
    }
    
    return "/error.html";
}

int main() {
    // Test cases
    printf("%s\\n", redirectUser("home")); // Should print /home.html
    printf("%s\\n", redirectUser("about")); // Should print /about.html
    printf("%s\\n", redirectUser("")); // Should print /error.html
    printf("%s\\n", redirectUser("../admin")); // Should print /error.html
    printf("%s\\n", redirectUser("<script>alert(1)</script>")); // Should print /error.html
    
    return 0;
}
