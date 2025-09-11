#include <stdio.h>
#include <string.h>

void processInput(char *input, char *output, size_t size) {
    // Process the input as needed. Here, we'll simply copy the input to output for demonstration.
    strncpy(output, input, size - 1);
    output[size - 1] = '\0'; // Ensuring null-termination
}

int main() {
    char input[256];
    char output[256];
    for (int i = 0; i < 5; ++i) {
        printf("Enter a string: ");
        if (fgets(input, sizeof(input), stdin)) {
            // Remove newline character if present
            input[strcspn(input, "\n")] = '\0';
            processInput(input, output, sizeof(output));
            printf("Processed string: %s\n", output);
        }
    }
    return 0;
}