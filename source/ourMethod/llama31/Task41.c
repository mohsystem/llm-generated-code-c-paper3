#include <stdio.h>
#include <string.h>

void processString(const char* inputStr) {
    if (inputStr == NULL || *inputStr == '\0') {
        printf("Input string is empty or null.\n");
        return;
    }
    printf("Processed string: %s\n", inputStr);
}

char* getUserInput() {
    char inputStr[1024]; // Fixed-size buffer to prevent overflow
    printf("Enter a string: ");
    fgets(inputStr, sizeof(inputStr), stdin);
    inputStr[strcspn(inputStr, "\n")] = 0; // Remove newline character
    return strdup(inputStr); // Allocate memory for the string
}

void mainWithTestCases() {
    const char* testCases[] = {"Hello, World!", "This is a test string", "", "Very long string to test buffer overflow safety"};
    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        processString(testCases[i]);
    }
}

int main() {
    // mainWithTestCases();
    char* inputStr = getUserInput();
    processString(inputStr);
    free(inputStr); // Free allocated memory
    return 0;
}