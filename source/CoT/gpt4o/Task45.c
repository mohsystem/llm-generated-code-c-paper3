#include <stdio.h>
#include <stdlib.h>

int processInput(int input) {
    if (input < 0) {
        printf("Negative input not allowed.\n");
        return -1;
    }
    return input * 2;
}

int main() {
    int testInputs[] = {10, -5, 15, 0, 3};
    size_t numTests = sizeof(testInputs) / sizeof(testInputs[0]);
    for (size_t i = 0; i < numTests; ++i) {
        int input = testInputs[i];
        printf("Processing input: %d\n", input);
        int result = processInput(input);
        printf("Result: %d\n", result);
    }
    return 0;
}