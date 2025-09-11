#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int convert_to_int(const char* str) {
    char* endptr;
    errno = 0;
    long num = strtol(str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0') {
        fprintf(stderr, "Invalid input: Cannot convert to integer.\n");
        exit(EXIT_FAILURE);
    }
    if (num < INT_MIN || num > INT_MAX) {
        fprintf(stderr, "Out of range: Cannot convert to integer.\n");
        exit(EXIT_FAILURE);
    }
    return (int)num;
}

int main() {
    const char* testCases[] = {"123", "abc", "123.45", "-123"};
    for (int i = 0; i < 4; ++i) {
        int num = convert_to_int(testCases[i]);
        printf("Converted integer: %d\n", num);
    }
    return EXIT_SUCCESS;
}