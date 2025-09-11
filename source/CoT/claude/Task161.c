
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int capacity, int* weights, int* values, int n) {
    if (capacity <= 0 || weights == NULL || values == NULL || n <= 0) {
        return 0;
    }
    
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(capacity + 1, sizeof(int));
    }
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    int result = dp[n][capacity];
    
    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    // Test case 1
    int weights1[] = {2, 3, 4, 5};
    int values1[] = {3, 4, 5, 6};
    printf("Test 1: %d\\n", knapsack(10, weights1, values1, 4)); // Expected: 13
    
    // Test case 2
    int weights2[] = {1, 2, 3};
    int values2[] = {6, 10, 12};
    printf("Test 2: %d\\n", knapsack(5, weights2, values2, 3)); // Expected: 22
    
    // Test case 3
    int weights3[] = {2, 5, 1, 3, 4};
    int values3[] = {6, 9, 1, 4, 7};
    printf("Test 3: %d\\n", knapsack(8, weights3, values3, 5)); // Expected: 20
    
    // Test case 4
    int weights4[] = {1, 3, 4, 5};
    int values4[] = {1, 4, 5, 7};
    printf("Test 4: %d\\n", knapsack(7, weights4, values4, 4)); // Expected: 9
    
    // Test case 5
    printf("Test 5: %d\\n", knapsack(5, NULL, NULL, 0)); // Expected: 0
    
    return 0;
}
