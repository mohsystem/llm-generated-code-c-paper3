#include<stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int sumBetween(int a, int b) {
    if (a == b) return a;
    int sum = 0;
    int start = min(a, b);
    int end = max(a, b);
    for (int i = start; i <= end; i++) {
        sum += i;
    }
    return sum;
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