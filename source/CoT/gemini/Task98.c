#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int convertToInt(const char *input) {
    char *endptr;
    long int val;

    errno = 0;    // Clear errno before calling strtol

    val = strtol(input, &endptr, 10);

    /* Check for various possible errors */
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        return -1;
    }

    if (endptr == input || *endptr != '\0') {
        return -1; // Not a valid integer
    }

    // Check for range exceeding int after converting from long int
    if (val > INT_MAX || val < INT_MIN) {
        return -1;
    }

    return (int)val;
}

int main() {
    char input[256]; // Increased buffer size to prevent potential overflow
    
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove trailing newline
    printf("%d\n", convertToInt(input));

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; 
    printf("%d\n", convertToInt(input));

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; 
    printf("%d\n", convertToInt(input));

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; 
    printf("%d\n", convertToInt(input));

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; 
    printf("%d\n", convertToInt(input));

    return 0;
}