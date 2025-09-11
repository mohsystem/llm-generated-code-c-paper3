#include <stdio.h>
#include <string.h>

void processString(const char *input, char *output, size_t max_size) {
    if (input == NULL) {
        strncpy(output, "", max_size);
        return;
    }
    // Example processing: Reverse the input string
    size_t len = strlen(input);
    for (size_t i = 0; i < len && i < max_size - 1; ++i) {
        output[i] = input[len - i - 1];
    }
    output[len < max_size ? len : max_size - 1] = '\0';
}

int main() {
    char input[256];
    char output[256];
    for (int i = 0; i < 5; ++i) {
        printf("Enter a string: ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // Remove newline character
            processString(input, output, sizeof(output));
            printf("Processed string: %s\n", output);
        }
    }
    return 0;
}