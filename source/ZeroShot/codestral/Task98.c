#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int convertToInt(const char* input) {
    char* end;
    long result = strtol(input, &end, 10);
    if (end == input || *end != '\0' || errno == ERANGE) {
        fprintf(stderr, "Input could not be converted to an integer\n");
        exit(EXIT_FAILURE);
    }
    return (int)result;
}

void testConversion(const char* input) {
    int result = convertToInt(input);
    if (result != EXIT_FAILURE) {
        printf("Successfully converted '%s' to %d\n", input, result);
    } else {
        printf("Failed to convert '%s' to an integer\n", input);
    }
}

int main() {
    testConversion("123");
    testConversion("456");
    testConversion("789");
    testConversion("abc");
    testConversion("123.456");
    return 0;
}