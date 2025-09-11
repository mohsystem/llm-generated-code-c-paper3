#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

void processString(const char* input) {
    printf("Processed string: %s\n", input);
}

int main() {
    char input[MAX_INPUT_SIZE];
    char* testCases[] = {"Hello", "World", "This is a test string", "Buffer overflow test", "Very long string to test buffer overflow"};
    
    for (int i = 0; i < 5; i++) {
        printf("Enter a string (or press Enter to use default '%s'): ", testCases[i]);
        fgets(input, MAX_INPUT_SIZE, stdin);
        input[strcspn(input, "\n")] = 0; // Remove the newline character
        if (input[0] == '\0') {
            strcpy(input, testCases[i]);
        }
        processString(input);
    }
    return 0;
}