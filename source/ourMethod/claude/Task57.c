
#include <stdio.h>
#include <stdlib.h>

long factorial(long n) {
    // Input validation
    if (n < 0) {
        fprintf(stderr, "Error: Factorial is not defined for negative numbers\\n");
        return -1;
    }
    if (n > 20) {
        fprintf(stderr, "Error: Number too large, would cause overflow\\n");
        return -1;
    }
    
    // Base case
    if (n == 0 || n == 1) {
        return 1;
    }
    
    // Calculate factorial
    long result = 1;
    for (long i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    // Test cases
    long tests[] = {0, 1, 5, 10, 20};
    int numTests = sizeof(tests)/sizeof(tests[0]);
    
    for (int i = 0; i < numTests; i++) {
        long result = factorial(tests[i]);
        if (result != -1) {
            printf("Factorial of %ld = %ld\\n", tests[i], result);
        }
    }
    return 0;
}
