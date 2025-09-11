#include <stdio.h>
#include <stdlib.h>

int sumBetween(int a, int b) {
    if (a == b) return a;
    int min_val = (a < b) ? a : b;
    int max_val = (a > b) ? a : b;
    return (max_val + min_val) * (max_val - min_val + 1) / 2;
}

int main() {
    printf("%d\n", sumBetween(1, 0)); // 1
    printf("%d\n", sumBetween(1, 2)); // 3
    printf("%d\n", sumBetween(0, 1)); // 1
    printf("%d\n", sumBetween(1, 1)); // 1
    printf("%d\n", sumBetween(-1, 0)); // -1
    printf("%d\n", sumBetween(-1, 2)); // 2
    return 0;
}