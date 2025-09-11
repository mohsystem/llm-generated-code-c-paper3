// C code
#include <stdio.h>
#include <stdlib.h>

int sumOfRange(int a, int b) {
    int min_val = (a < b) ? a : b;
    int max_val = (a > b) ? a : b;
    int sum_val = 0;
    for (int i = min_val; i <= max_val; i++) {
        sum_val += i;
    }
    return sum_val;
}

int main() {
    printf("%d\n", sumOfRange(1, 0)); // Expected: 1
    printf("%d\n", sumOfRange(1, 2)); // Expected: 3
    printf("%d\n", sumOfRange(0, 1)); // Expected: 1
    printf("%d\n", sumOfRange(1, 1)); // Expected: 1
    printf("%d\n", sumOfRange(-1, 0)); // Expected: -1
    printf("%d\n", sumOfRange(-1, 2)); // Expected: 2
    return 0;
}