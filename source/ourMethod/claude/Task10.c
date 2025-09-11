
#include <stdio.h>

// Helper function to find minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Helper function to find maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

int getSum(int a, int b) {
    if (a == b) return a;
    
    int start = min(a, b);
    int end = max(a, b);
    
    // Using arithmetic progression sum formula to avoid overflow
    int n = end - start + 1;
    // Cast to long long to prevent integer overflow during calculation
    long long sum = ((long long)n * (start + end)) / 2;
    
    // Check if result is within integer bounds
    if (sum > INT_MAX || sum < INT_MIN) {
        // In C we can't throw exceptions, so return INT_MIN to indicate error
        return INT_MIN;
    }
    
    return (int)sum;
}

int main() {
    // Test cases
    printf("%d\\n", getSum(1, 0));   // Expected: 1
    printf("%d\\n", getSum(1, 2));   // Expected: 3
    printf("%d\\n", getSum(0, 1));   // Expected: 1
    printf("%d\\n", getSum(1, 1));   // Expected: 1
    printf("%d\\n", getSum(-1, 2));  // Expected: 2
    return 0;
}
