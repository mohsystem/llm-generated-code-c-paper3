
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapSack(int capacity, int weights[], int values[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for(int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
    }
    
    for(int i = 0; i <= n; i++) {
        for(int w = 0; w <= capacity; w++) {
            if(i == 0 || w == 0)
                dp[i][w] = 0;
            else if(weights[i-1] <= w)
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
    // Test Case 1
    int values1[] = {60, 100, 120};
    int weights1[] = {10, 20, 30};
    int capacity1 = 50;
    printf("Test Case 1: %d\\n", knapSack(capacity1, weights1, values1, 3));

    // Test Case 2
    int values2[] = {10, 40, 30, 50};
    int weights2[] = {5, 4, 6, 3};
    int capacity2 = 10;
    printf("Test Case 2: %d\\n", knapSack(capacity2, weights2, values2, 4));

    // Test Case 3
    int values3[] = {100, 200, 300};
    int weights3[] = {10, 20, 30};
    int capacity3 = 40;
    printf("Test Case 3: %d\\n", knapSack(capacity3, weights3, values3, 3));

    // Test Case 4
    int values4[] = {5, 10, 15, 20, 25};
    int weights4[] = {2, 4, 6, 8, 10};
    int capacity4 = 20;
    printf("Test Case 4: %d\\n", knapSack(capacity4, weights4, values4, 5));

    // Test Case 5
    int values5[] = {1, 2, 3};
    int weights5[] = {4, 5, 6};
    int capacity5 = 3;
    printf("Test Case 5: %d\\n", knapSack(capacity5, weights5, values5, 3));

    return 0;
}
