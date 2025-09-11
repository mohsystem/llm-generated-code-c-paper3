#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertToInt(const char *input) {
    char *endptr;
    long int result = strtol(input, &endptr, 10);
    if (*endptr != '\0' || (result > INT_MAX || result < INT_MIN)) {
        return -1; 
    }
    return (int)result;
}

int main() {
    char input[256]; // Adjust size as needed
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