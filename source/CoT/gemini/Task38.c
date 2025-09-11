#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A simple HTML escaping function (not exhaustive)
void escapeHtml(const char* input, char* output, size_t outputSize) {
    size_t i = 0, j = 0;
    while (input[i] != '\0' && j < outputSize - 1) {
        switch (input[i]) {
            case '<': strncpy(output + j, "&lt;", 4); j += 4; break;
            case '>': strncpy(output + j, "&gt;", 4); j += 4; break;
            case '&': strncpy(output + j, "&amp;", 5); j += 5; break;
            case '"': strncpy(output + j, "&quot;", 6); j += 6; break;
            case '\'': strncpy(output + j, "&#x27;", 6); j += 6; break;
            case '/': strncpy(output + j, "&#x2F;", 6); j += 6; break;
            default: output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0'; // Null-terminate the output string
}


int main() {
    const char* testInputs[] = {"Hello, world!", "<script>alert('XSS!')</script>", "Test & Test", "\"", "''''''"};
    
    for (int i = 0; i < sizeof(testInputs) / sizeof(testInputs[0]); i++) {
        char escapedOutput[1024]; // Make sure the buffer is large enough
        escapeHtml(testInputs[i], escapedOutput, sizeof(escapedOutput));
        printf("Input: %s\n", testInputs[i]);
        printf("Escaped Output: %s\n\n", escapedOutput);
    }
    
    return 0;
}