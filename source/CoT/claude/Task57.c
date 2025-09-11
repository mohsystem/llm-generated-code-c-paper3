
#include <stdio.h>
#include <stdlib.h>

long long calculateFactorial(int n) {
    if (n < 0) {
        printf("Error: Factorial is not defined for negative numbers\\n");
        exit(1);
    }
    if (n > 20) {
        printf("Error: Input too large, may cause overflow\\n");
        exit(1);
    }
    
    long long result = 1;
    for(int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("Factorial of 5: %lld\\n", calculateFactorial(5));   // 120
    printf("Factorial of 0: %lld\\n", calculateFactorial(0));   // 1
    printf("Factorial of 10: %lld\\n", calculateFactorial(10)); // 3628800
    printf("Factorial of 3: %lld\\n", calculateFactorial(3));   // 6
    printf("Factorial of 7: %lld\\n", calculateFactorial(7));   // 5040
    
    return 0;
}
