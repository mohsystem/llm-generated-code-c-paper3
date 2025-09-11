// C program to find factorial of given number
#include <stdio.h>

// Function to find factorial of given number
long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Driver code
int main() {
    int testCases[] = {0, 1, 5, 10, 15};
    int size = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < size; i++) {
        printf("Factorial of %d is %lld\n", testCases[i], factorial(testCases[i]));
    }
    return 0;
}