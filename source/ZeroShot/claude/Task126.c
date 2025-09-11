
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

void sanitizeInput(char *input, char *output) {
    int j = 0;
    for(int i = 0; input[i]; i++) {
        if(isalnum((unsigned char)input[i])) {
            output[j++] = tolower((unsigned char)input[i]);
        }
    }
    output[j] = '\\0';
}

const char* redirectPage(const char *userInput) {
    if(userInput == NULL || strlen(userInput) == 0) {
        return "error.html";
    }
    
    char sanitized[MAX_LENGTH];
    sanitizeInput((char*)userInput, sanitized);
    
    if(strcmp(sanitized, "home") == 0) return "home.html";
    if(strcmp(sanitized, "about") == 0) return "about.html";
    if(strcmp(sanitized, "contact") == 0) return "contact.html";
    if(strcmp(sanitized, "products") == 0) return "products.html";
    return "error.html";
}

int main() {
    // Test cases
    printf("%s\\n", redirectPage("home")); // home.html
    printf("%s\\n", redirectPage("about")); // about.html
    printf("%s\\n", redirectPage("<script>alert(1)</script>")); // error.html
    printf("%s\\n", redirectPage("")); // error.html
    printf("%s\\n", redirectPage("products")); // products.html
    return 0;
}
