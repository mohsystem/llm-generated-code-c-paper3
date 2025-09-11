#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void testCases() {
    char* inputs[] = {"10", "20", "abc", "30.5", "40"};
    for (int i = 0; i < 5; i++) {
        char* endptr;
        errno = 0;
        long number = strtol(inputs[i], &endptr, 10);
        if (errno == 0 && *endptr == '\0') {
            printf("Input: %s, Result: %ld\n", inputs[i], number * 2);
        } else {
            double dnumber = strtod(inputs[i], &endptr);
            if (errno == 0 && *endptr == '\0') {
                printf("Input: %s, Result: %.2f\n", inputs[i], dnumber * 2);
            } else {
                printf("Input: %s, Error: Invalid input\n", inputs[i]);
            }
        }
    }
}

int main() {
    testCases();
    return 0;
}