
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int capacity, int* weights, int* values, int n) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for(int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(capacity + 1, sizeof(int));
    }
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i-1] <= w)
                dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    
    int result = dp[n][capacity];
    
    // Free allocated memory
    for(int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    // Test case 1
    int values1[] = {60, 100, 120};
    int weights1[] = {10, 20, 30};
    int capacity1 = 50;
    printf("Test 1: %d\\n", knapsack(capacity1, weights1, values1, 3));

    // Test case 2
    int values2[] = {10, 20, 30, 40};
    int weights2[] = {1, 2, 3, 4};
    int capacity2 = 5;
    printf("Test 2: %d\\n", knapsack(capacity2, weights2, values2, 4));

    // Test case 3
    int values3[] = {5, 10, 15, 20, 25};
    int weights3[] = {2, 4, 6, 8, 10};
    int capacity3 = 15;
    printf("Test 3: %d\\n", knapsack(capacity3, weights3, values3, 5));

    // Test case 4
    int values4[] = {1, 2, 3};
    int weights4[] = {4, 5, 6};
    int capacity4 = 3;
    printf("Test 4: %d\\n", knapsack(capacity4, weights4, values4, 3));

    // Test case 5
    int values5[] = {100};
    int weights5[] = {1};
    int capacity5 = 1;
    printf("Test 5: %d\\n", knapsack(capacity5, weights5, values5, 1));

    return 0;
}
