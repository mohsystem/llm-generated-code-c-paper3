
// C (using CGI)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

void Task38_sanitize_input(char *input, char *output) {
    while (*input) {
        switch(*input) {
            case '<':
                strcat(output, "&lt;");
                break;
            case '>':
                strcat(output, "&gt;");
                break;
            case '&':
                strcat(output, "&amp;");
                break;
            case '"':
                strcat(output, "&quot;");
                break;
            case '\'': //todo error: missing terminating ' character
                strcat(output, "&#39;");
                break;
            default:
                if (isprint(*input)) {
                    char temp[2] = {*input, '\\0'};
                    strcat(output, temp);
                }
        }
        input++;
    }
}

int main(void) {
    char *requestMethod = getenv("REQUEST_METHOD");
    
    printf("Content-type: text/html\\n\\n");
    printf("<!DOCTYPE html>\\n<html>\\n<head><title>Form</title></head>\\n<body>\\n");

    if (requestMethod && strcmp(requestMethod, "POST") == 0) {
        char input[MAX_INPUT] = {0};
        char sanitized[MAX_INPUT * 6] = {0};  // Allow space for HTML entities
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        
        if (content_length < MAX_INPUT) {
            fgets(input, content_length + 1, stdin);
            
            // Extract userInput value
            char *userInput = strstr(input, "userInput=");
            if (userInput) {
                userInput += 10;  // Skip "userInput="
                Task38_sanitize_input(userInput, sanitized);
                
                printf("<h2>Your input:</h2>\\n");
                printf("<p>%s</p>\\n", sanitized);
            }
        }
    } else {
        printf("<form method='post' action=''>\\n");
        printf("<input type='text' name='userInput' required>\\n");
        printf("<button type='submit'>Submit</button>\\n");
        printf("</form>\\n");
    }
    
    printf("</body>\\n</html>");
    return 0;
}
