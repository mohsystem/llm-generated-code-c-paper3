#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int convertToInteger(const char* input) {
    char* end;
    long value = strtol(input, &end, 10);

    if (end == input || *end != '\0' || value < INT_MIN || value > INT_MAX) {
        printf("Invalid input. Please enter a valid integer.\n");
        return INT_MIN;
    }

    return (int)value;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        int result = convertToInteger(argv[1]);
        if (result != INT_MIN) {
            printf("Converted integer: %d\n", result);
        }
    } else {
        printf("Please provide a string input as a command line argument.\n");
    }

    return 0;
}