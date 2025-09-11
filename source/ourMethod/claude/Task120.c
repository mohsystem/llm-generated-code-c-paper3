
// Task120.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100
#define MAX_OUTPUT_LENGTH 500

void escapeHtml(const char* input, char* output, size_t outputSize) {
    size_t inputLen = strlen(input);
    size_t outputIndex = 0;
    
    for (size_t i = 0; i < inputLen && outputIndex < outputSize - 1; i++) {
        switch(input[i]) {
            case '&':
                if (outputIndex + 5 >= outputSize) break;
                strcpy(output + outputIndex, "&amp;");
                outputIndex += 5;
                break;
            case '<':
                if (outputIndex + 4 >= outputSize) break;
                strcpy(output + outputIndex, "&lt;");
                outputIndex += 4;
                break;
            case '>':
                if (outputIndex + 4 >= outputSize) break;
                strcpy(output + outputIndex, "&gt;");
                outputIndex += 4;
                break;
            case '"':
                if (outputIndex + 6 >= outputSize) break;
                strcpy(output + outputIndex, "&quot;");
                outputIndex += 6;
                break;
            case '\\'':
                if (outputIndex + 6 >= outputSize) break;
                strcpy(output + outputIndex, "&#39;");
                outputIndex += 6;
                break;
            default:
                output[outputIndex++] = input[i];
        }
    }
    output[outputIndex] = '\\0';
}

void generateHtml(const char* userInput) {
    char escapedInput[MAX_OUTPUT_LENGTH];
    escapeHtml(userInput, escapedInput, sizeof(escapedInput));
    
    printf("Content-Type: text/html\\n\\n");
    printf("<!DOCTYPE html>\\n"
           "<html>\\n"
           "<head>\\n"
           "<title>Display Input</title>\\n"
           "</head>\\n"
           "<body>\\n");
    
    if (strlen(userInput) > 0) {
        printf("<p>You entered: %s</p>\\n", escapedInput);
    }
    
    printf("<form method='get'>\\n"
           "<input type='text' name='input' maxlength='%d'>\\n"
           "<input type='submit' value='Submit'>\\n"
           "</form>\\n"
           "</body>\\n"
           "</html>", MAX_INPUT_LENGTH);
}

int main() {
    // Test cases
    const char* testInputs[] = {
        "Hello World",
        "<script>alert('xss')</script>",
        "Test & <> \\"'",
        "Normal text 123",
        "" // Empty input
    };
    
    for (int i = 0; i < 5; i++) {
        char escaped[MAX_OUTPUT_LENGTH];
        printf("Input: %s\\n", testInputs[i]);
        escapeHtml(testInputs[i], escaped, sizeof(escaped));
        printf("Escaped: %s\\n\\n", escaped);
    }
    
    return 0;
}
