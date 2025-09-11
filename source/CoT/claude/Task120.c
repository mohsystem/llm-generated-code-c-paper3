
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

// Structure to store sanitized input
typedef struct {
    char sanitized[MAX_INPUT];
} Task120;

// Function to sanitize input
void sanitizeInput(const char* input, char* output) {
    int j = 0;
    for(int i = 0; input[i] != '\\0' && j < MAX_INPUT-1; i++) {
        switch(input[i]) {
            case '&':
                strcpy(&output[j], "&amp;");
                j += 5;
                break;
            case '<':
                strcpy(&output[j], "&lt;");
                j += 4;
                break;
            case '>':
                strcpy(&output[j], "&gt;");
                j += 4;
                break;
            case '"':
                strcpy(&output[j], "&quot;");
                j += 6;
                break;
            case '\\'':
                strcpy(&output[j], "&#x27;");
                j += 6;
                break;
            default:
                if(isprint(input[i])) {
                    output[j++] = input[i];
                }
        }
    }
    output[j] = '\\0';
}

void displayWebPage(const char* userInput) {
    printf("Content-Type: text/html\\n\\n");
    printf("<!DOCTYPE html>\\n");
    printf("<html><body>\\n");
    printf("<form method='post'>\\n");
    printf("Enter text: <input type='text' name='userInput'>\\n");
    printf("<input type='submit' value='Submit'>\\n");
    printf("</form>\\n");
    
    if(userInput != NULL) {
        Task120 task;
        sanitizeInput(userInput, task.sanitized);
        printf("<h2>Your input:</h2>\\n");
        printf("<p>%s</p>\\n", task.sanitized);
    }
    
    printf("</body></html>\\n");
}

int main() {
    // Test cases
    const char* testInputs[] = {
        "Hello World",
        "<script>alert('XSS')</script>",
        "Test & Test",
        "Quote\\"Test",
        "Single'Quote"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("\\nTest Case %d:\\n", i+1);
        displayWebPage(testInputs[i]);
    }
    
    return 0;
}
