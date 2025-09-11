
#include <stdio.h>
#include <limits.h>

long long factorial(int n) {
    if (n < 0) return -1;
    if (n == 0 || n == 1) return 1;
    
    long long result = 1;
    for(int i = 2; i <= n; i++) {
        if (result > LLONG_MAX/i) return -1; //check overflow
        result *= i;
    }
    return result;
}

int main() {
    int testCases[] = {5, 0, 10, 3, 7};
    int numTests = 5;
    
    for(int i = 0; i < numTests; i++) {
        printf("Factorial of %d = %lld\\n", testCases[i], factorial(testCases[i]));
    }
    return 0;
}
