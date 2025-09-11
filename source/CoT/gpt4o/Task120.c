#include <stdio.h>
#include <string.h>

void escapeHtml(const char* input, char* output) {
    while (*input) {
        switch (*input) {
            case '&': strcat(output, "&amp;"); break;
            case '\"': strcat(output, "&quot;"); break;
            case '\'': strcat(output, "&apos;"); break;
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            default: strncat(output, input, 1); break;
        }
        input++;
    }
}

void displayInput(const char* userInput) {
    char escapedInput[1024] = {0};
    escapeHtml(userInput, escapedInput);
    printf("<h2>User Input:</h2><p>%s</p>\n", escapedInput);
}

int main() {
    const char* testInputs[5] = {
        "<script>alert('XSS')</script>",
        "Hello, World!",
        "C <3",
        "\"Test\"",
        "Use 'single quotes'"
    };

    for(int i = 0; i < 5; i++) {
        displayInput(testInputs[i]);
    }

    return 0;
}