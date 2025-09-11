#include <stdio.h>
#include <stdlib.h>

int knapSack(int* values, int* weights, int n, int capacity) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((capacity + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (weights[i - 1] <= j) {
                dp[i][j] = (values[i - 1] + dp[i - 1][j - weights[i - 1]] > dp[i - 1][j]) ? values[i - 1] + dp[i - 1][j - weights[i - 1]] : dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int result = dp[n][capacity];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int values[] = {30, 10, 40, 20};
    int weights[] = {10, 20, 30, 40};
    int capacity = 40;
    int n = sizeof(values) / sizeof(values[0]);
    printf("Knapsack value is: %d\n", knapSack(values, weights, n, capacity));

    // Test cases
    int valuesTest[][6] = {
        {10, 20, 30, 40, 60, 70},
        {60, 100, 120},
        {10, 20, 30},
        {5, 10, 15},
        {20, 30, 40}
    };
    int weightsTest[][6] = {
        {1, 2, 3, 6, 7, 4},
        {10, 20, 30},
        {1, 2, 3},
        {1, 2, 3},
        {5, 10, 15}
    };
    int capacitiesTest[] = {7, 50, 5, 5, 20};

    for (int i = 0; i < 5; i++) {
        int nTest = (i == 1 || i == 2 || i == 3) ? 3 : (i == 4) ? 3 : 6;
        printf("Knapsack value for test case %d is: %d\n", i + 1, knapSack(valuesTest[i], weightsTest[i], nTest, capacitiesTest[i]));
    }
    return 0;
}