#include <stdio.h>

int processInput(int input) {
    return input * 2;
}

int main() {
    int testCases[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        int result = processInput(testCases[i]);
        printf("Result: %d\n", result);
    }
    return 0;
}