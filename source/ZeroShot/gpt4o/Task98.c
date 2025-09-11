#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int convertToInt(const char *input) {
    char *end;
    long number = strtol(input, &end, 10);
    if (end == input || *end != '\0' || number > INT_MAX || number < INT_MIN) {
        return INT_MAX; // Indicating invalid input
    }
    return (int)number;
}

int main() {
    printf("Enter 5 numbers:\n");
    for (int i = 0; i < 5; i++) {
        char input[256];
        if (fgets(input, sizeof(input), stdin)) {
            // Remove newline character
            input[strcspn(input, "\n")] = 0;
            int result = convertToInt(input);
            if (result != INT_MAX) {
                printf("Converted: %d\n", result);
            } else {
                printf("Invalid input, not an integer.\n");
            }
        }
    }
    return 0;
}