#include <stdio.h>
#include <string.h>

void secureInput(const char* input, int bufferSize) {
    if (strlen(input) > bufferSize) {
        printf("Input exceeds buffer size. Truncating input.\n");
        char truncatedInput[bufferSize + 1];
        strncpy(truncatedInput, input, bufferSize);
        truncatedInput[bufferSize] = '\0';
        printf("Input: %s\n", truncatedInput);
    } else {
        printf("Input: %s\n", input);
    }
}

void testCases() {
    secureInput("Hello", 10);
    secureInput("This is a very long input", 10);
    secureInput("Short", 10);
    secureInput("Another long input that will be truncated", 10);
    secureInput("Just right", 10);
}

int main() {
    testCases();
    return 0;
}