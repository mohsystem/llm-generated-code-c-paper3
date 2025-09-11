
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUTPUT_LENGTH 1024

char* displayUserInput(const char* userInput) {
    if (userInput == NULL) {
        char* result = (char*)malloc(1);
        result[0] = '\\0';
        return result;
    }
    
    // Allocate memory for the result
    char* result = (char*)malloc(MAX_OUTPUT_LENGTH);
    if (result == NULL) {
        return NULL;
    }
    
    // Initialize the result with opening paragraph tag
    strcpy(result, "<p>");
    int pos = 3; // Starting after "<p>"
    
    // Process each character
    for (int i = 0; userInput[i] != '\\0' && pos < MAX_OUTPUT_LENGTH - 8; i++) {
        switch(userInput[i]) {
            case '&':
                strcat(result + pos, "&amp;");
                pos += 5;
                break;
            case '<':
                strcat(result + pos, "&lt;");
                pos += 4;
                break;
            case '>':
                strcat(result + pos, "&gt;");
                pos += 4;
                break;
            case '"':
                strcat(result + pos, "&quot;");
                pos += 6;
                break;
            case '\\'':
                strcat(result + pos, "&#x27;");
                pos += 6;
                break;
            case '/':
                strcat(result + pos, "&#x2F;");
                pos += 6;
                break;
            default:
                result[pos++] = userInput[i];
                result[pos] = '\\0';
        }
    }
    
    // Add closing paragraph tag
    strcat(result, "</p>");
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = displayUserInput("Hello World");
    printf("%s\\n", result);
    free(result);
    
    result = displayUserInput("<script>alert('XSS')</script>");
    printf("%s\\n", result);
    free(result);
    
    result = displayUserInput("Text with & < > \\" ' / symbols");
    printf("%s\\n", result);
    free(result);
    
    result = displayUserInput(NULL);
    printf("%s\\n", result);
    free(result);
    
    result = displayUserInput("Regular text 123");
    printf("%s\\n", result);
    free(result);
    
    return 0;
}
