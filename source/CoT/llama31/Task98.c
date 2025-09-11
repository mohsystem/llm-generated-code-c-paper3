#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void testCases() {
    const char* inputs[] = {"123", "abc", "123.45", "-123", "0"};
    for (int i = 0; i < 5; i++) {
        char* endptr;
        errno = 0;
        long result = strtol(inputs[i], &endptr, 10);
        if (errno == ERANGE || *endptr != '\0' || errno != 0) {
            printf("Input: %s, Output: Not an integer\n", inputs[i]);
        } else {
            printf("Input: %s, Output: %ld\n", inputs[i], result);
        }
    }
}

int main() {
    testCases();
    return 0;
}