#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int convertStringToInt(const char* str) {
    char* endptr;
    errno = 0;
    long num = strtol(str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || num > INT_MAX || num < INT_MIN) {
        fprintf(stderr, "Invalid input or out of range for an integer.\n");
        exit(EXIT_FAILURE);
    }
    return (int)num;
}

int main() {
    const char* testCases[] = {"123", "456", "abc", "789", "123.45"};
    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        int number = convertStringToInt(testCases[i]);
        printf("Converted integer: %d\n", number);
    }
    return 0;
}