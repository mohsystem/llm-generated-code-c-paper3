#include <stdio.h>
#include <string.h>
#include <ctype.h>

void processString(char* input, char* output) {
    // Example processing: convert to uppercase
    for (int i = 0; i < strlen(input); i++) {
        output[i] = toupper(input[i]);
    }
    output[strlen(input)] = '\0'; // Null-terminate the string
}

int main() {
    char input[100];
    char output[100];

    const char* testCases[] = {"hello", "world", "this is a test", "buffer overflow test", "secure coding"};
    for (int i = 0; i < 5; i++) {
        strncpy(input, testCases[i], sizeof(input));
        input[sizeof(input) - 1] = '\0'; // Ensure null-termination

        processString(input, output);
        printf("Input: %s, Output: %s\n", input, output);
    }

    return 0;
}