
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 100

void sanitizeInput(char* input) {
    // Convert to lowercase and trim
    int start = 0, end = strlen(input) - 1;
    
    // Trim leading spaces
    while(isspace(input[start])) start++;
    
    // Trim trailing spaces
    while(end > start && isspace(input[end])) end--;
    
    // Shift characters to beginning of string
    int i;
    for(i = 0; i <= end-start; i++) {
        input[i] = tolower(input[start + i]);
    }
    input[i] = '\\0';
}

const char* getRedirectPage(char* userInput) {
    // Input validation
    if(userInput == NULL || strlen(userInput) == 0) {
        return "error.html";
    }
    
    // Create a temporary buffer for sanitization
    char sanitizedInput[MAX_INPUT_LENGTH];
    strncpy(sanitizedInput, userInput, MAX_INPUT_LENGTH-1);
    sanitizedInput[MAX_INPUT_LENGTH-1] = '\\0';
    
    sanitizeInput(sanitizedInput);
    
    // Redirection logic
    if(strcmp(sanitizedInput, "home") == 0) {
        return "home.html";
    } else if(strcmp(sanitizedInput, "about") == 0) {
        return "about.html";
    } else if(strcmp(sanitizedInput, "contact") == 0) {
        return "contact.html";
    } else if(strcmp(sanitizedInput, "products") == 0) {
        return "products.html";
    } else if(strcmp(sanitizedInput, "services") == 0) {
        return "services.html";
    }
    
    return "error.html";
}

int main() {
    // Test cases
    char input1[] = "home";
    char input2[] = "ABOUT";
    char input3[] = "contact  ";
    char input4[] = "";
    char input5[] = "invalid";
    
    printf("%s\\n", getRedirectPage(input1));  // Should print home.html
    printf("%s\\n", getRedirectPage(input2));  // Should print about.html
    printf("%s\\n", getRedirectPage(input3));  // Should print contact.html
    printf("%s\\n", getRedirectPage(input4));  // Should print error.html
    printf("%s\\n", getRedirectPage(input5));  // Should print error.html
    
    return 0;
}
