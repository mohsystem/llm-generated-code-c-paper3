#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int convertToInt(const char *input) {
    char *endptr;
    long int result;

    errno = 0; // Clear errno before calling strtol
    result = strtol(input, &endptr, 10);

    if (errno == ERANGE) {
        // Overflow or underflow occurred
        return -1;
    } else if (endptr == input || *endptr != '\0') {
        // Invalid input (non-numeric characters)
        return -1;
    } else if (result > INT_MAX || result < INT_MIN) {
        // Result out of range for int
        return -1;
    } else {
        return (int)result;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide input as command line arguments.\n");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        int result = convertToInt(argv[i]);
        if (result != -1) {
            printf("Converted value: %d\n", result);
        } else {
            printf("Invalid input: %s\n", argv[i]);
        }
    }

    // Test cases
    printf("%d\n", convertToInt("123"));  // Output: 123
    printf("%d\n", convertToInt("-456")); // Output: -456
    printf("%d\n", convertToInt("0"));   // Output: 0
    printf("%d\n", convertToInt("123a")); // Output: -1 
    printf("%d\n", convertToInt("1.23")); // Output: -1 

    return 0;
}