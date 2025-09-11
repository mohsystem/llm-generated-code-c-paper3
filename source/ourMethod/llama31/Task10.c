#include <stdio.h>

int sumBetween(int a, int b) {
    // Ensure a is the smaller number
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    // Calculate the sum using the formula for the sum of an arithmetic series
    int sum = (b - a + 1) * (a + b) / 2;
    return sum;
}

int main() {
    // Test cases
    printf("%d\n", sumBetween(1, 0));   // 1
    printf("%d\n", sumBetween(1, 2));   // 3
    printf("%d\n", sumBetween(0, 1));   // 1
    printf("%d\n", sumBetween(1, 1));   // 1
    printf("%d\n", sumBetween(-1, 0)); // -1
    printf("%d\n", sumBetween(-1, 2)); // 2
    return 0;
}