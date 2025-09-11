#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int stringToInt(const char* input) {
    char *endptr;
    long int result;

    errno = 0; // Clear errno before calling strtol
    result = strtol(input, &endptr, 10);

    if (errno == ERANGE) {
        // Overflow or underflow occurred
      return -1;
    }
    if (endptr == input || *endptr != '\0') {
        // Not a valid integer string
        return -1;
    }
    // Check for overflow after conversion to int.
    if (result > INT_MAX || result < INT_MIN) {
       return -1;
    }


    return (int)result;
}

int main(int argc, char* argv[]) {
    printf("%d\n", stringToInt("123"));      // Output: 123
    printf("%d\n", stringToInt("-456"));     // Output: -456
    printf("%d\n", stringToInt("0"));        // Output: 0
    printf("%d\n", stringToInt("123a"));    // Output: -1
    printf("%d\n", stringToInt("123.45"));  // Output: -1


    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            int result = stringToInt(argv[i]);
            if (result != -1) {
                printf("Successfully converted %s to integer: %d\n", argv[i], result);
            } else {
                printf("Failed to convert %s to integer.\n", argv[i]);
            }
        }
    } else {
        printf("No command line arguments provided.\n");

        char input[256]; // Limit input size to prevent potential buffer overflow

        printf("Enter a string: ");

        if (fgets(input, sizeof(input), stdin) != NULL) {
           input[strcspn(input, "\n")] = 0; // Remove trailing newline.

            int result = stringToInt(input);
            if (result != -1) {
                printf("Successfully converted to integer: %d\n", result);
            } else {
                printf("Failed to convert to integer.\n");
            }
        } else {
           printf("Error reading input.\n");
           return 1; // Indicate an error.
        }
    }

    return 0;
}