// C code
#include <stdio.h>

// Function to find factorial of given number
long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    long res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

int main() {
    int testCases[] = {0, 1, 2, 5, 10};
    int size = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < size; i++) {
        printf("Factorial of %d is %ld\n", testCases[i], factorial(testCases[i]));
    }
    return 0;
}