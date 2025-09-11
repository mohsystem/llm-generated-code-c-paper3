#include <stdio.h>
#include <string.h>

void processString(const char* input, char* output, size_t size) {
    // Process the string and return it, here we just copy the input to output for simplicity
    strncpy(output, input, size - 1);
    output[size - 1] = '\0';  // Ensure null-termination
}

int main() {
    char input[256];
    char output[256];
    printf("Enter a string:\n");

    for (int i = 0; i < 5; i++) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline character from input
        processString(input, output, sizeof(output));
        printf("Processed string: %s\n", output);
    }

    return 0;
}