
#include <stdio.h>
#include <stdlib.h>

int knapsack(int capacity, int* weights, int* values, int n) {
    if (capacity <= 0 || weights == NULL || values == NULL || n <= 0) {
        return 0;
    }
    
    // Allocate 2D array for dynamic programming
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    if (dp == NULL) return 0;
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(capacity + 1, sizeof(int));
        if (dp[i] == NULL) {
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    
    // Fill dp table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                int val1 = values[i-1] + dp[i-1][w-weights[i-1]];
                int val2 = dp[i-1][w];
                dp[i][w] = (val1 > val2) ? val1 : val2;
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    // Store result before freeing memory
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
    printf("Test 1: %d\\n", knapsack(10, weights1, values1, 4));  // Expected: 13
    
    // Test case 2
    int weights2[] = {1, 2, 3};
    int values2[] = {6, 10, 12};
    printf("Test 2: %d\\n", knapsack(5, weights2, values2, 3));  // Expected: 22
    
    // Test case 3
    int weights3[] = {10, 20, 30};
    int values3[] = {60, 100, 120};
    printf("Test 3: %d\\n", knapsack(50, weights3, values3, 3));  // Expected: 220
    
    // Test case 4: NULL input
    printf("Test 4: %d\\n", knapsack(10, NULL, NULL, 0));  // Expected: 0
    
    // Test case 5: Invalid capacity
    printf("Test 5: %d\\n", knapsack(-1, weights1, values1, 4));  // Expected: 0
    
    return 0;
}
