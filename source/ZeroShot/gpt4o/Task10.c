#include <stdio.h>

int sumBetween(int a, int b) {
    int minVal = a < b ? a : b;
    int maxVal = a > b ? a : b;
    int sum = 0;
    for (int i = minVal; i <= maxVal; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    printf("%d\n", sumBetween(1, 0));  // 1
    printf("%d\n", sumBetween(1, 2));  // 3
    printf("%d\n", sumBetween(0, 1));  // 1
    printf("%d\n", sumBetween(1, 1));  // 1
    printf("%d\n", sumBetween(-1, 2)); // 2
    return 0;
}