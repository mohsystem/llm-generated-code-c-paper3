#include <stdio.h>

int sumBetween(int a, int b) {
    int sum = 0;
    int start = a < b ? a : b;
    int end = a > b ? a : b;
    for (int i = start; i <= end; ++i) {
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