#include <stdio.h>
#include <stdlib.h>

void testCases() {
    const char* inputs[] = {"10", "abc", "20", "-5", "30"};
    for (int i = 0; i < 5; ++i) {
        char* endptr;
        int number = strtol(inputs[i], &endptr, 10);
        if (*endptr != '\0') {
            printf("Error: Invalid input - %s\n", inputs[i]);
        } else {
            int result = processInput(number);
            printf("Input: %d, Result: %d\n", number, result);
        }
    }
}

int processInput(int number) {
    if (number < 0) {
        fprintf(stderr, "Error: Negative number\n");
        return 0;
    }
    return number * 2;
}

int main() {
    testCases();
    return 0;
}