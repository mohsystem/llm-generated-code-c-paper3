#include <stdio.h>

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    printf("%d\n", factorial(5));   // 120
    printf("%d\n", factorial(0));   // 1
    printf("%d\n", factorial(1));   // 1
    printf("%d\n", factorial(3));   // 6
    printf("%d\n", factorial(10));  // 3628800
    return 0;
}