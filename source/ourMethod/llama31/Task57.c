#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main_function() {
    // Test cases
    int numbers[] = {0, 1, 2, 5, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < size; i++) {
        printf("Factorial of %d is %lld\n", numbers[i], factorial(numbers[i]));
    }
}

long long factorial(int n) {
    if (n < 0) {
        fprintf(stderr, "Factorial is not defined for negative numbers\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
        // Check for overflow
        if (result > LLONG_MAX / i) {
            fprintf(stderr, "Factorial result exceeds LLONG_MAX\n");
            exit(EXIT_FAILURE);
        }
    }
    return result;
}

int main() {
    main_function();
    return 0;
}