#include <stdio.h>
#include <stdlib.h>

int knapsack(int capacity, int* weights, int* values, int n) {
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

    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    // Test cases
    int weights1[] = {10, 20, 30, 40};
    int values1[] = {30, 10, 40, 20};
    int capacity1 = 40;
    int n1 = sizeof(values1) / sizeof(values1[0]);
    printf("Maximum value for test case 1: %d\n", knapsack(capacity1, weights1, values1, n1));

    int weights2[] = {1, 2, 3, 6, 7, 4};
    int values2[] = {10, 20, 30, 40, 60, 70};
    int capacity2 = 7;
    int n2 = sizeof(values2) / sizeof(values2[0]);
    printf("Maximum value for test case 2: %d\n", knapsack(capacity2, weights2, values2, n2));

    int weights3[] = {5, 10, 15};
    int values3[] = {50, 100, 150};
    int capacity3 = 25;
    int n3 = sizeof(values3) / sizeof(values3[0]);
    printf("Maximum value for test case 3: %d\n", knapsack(capacity3, weights3, values3, n3));

    int weights4[] = {2, 3, 5};
    int values4[] = {10, 20, 30};
    int capacity4 = 6;
    int n4 = sizeof(values4) / sizeof(values4[0]);
    printf("Maximum value for test case 4: %d\n", knapsack(capacity4, weights4, values4, n4));

    int weights5[] = {1, 1, 1};
    int values5[] = {10, 20, 30};
    int capacity5 = 2;
    int n5 = sizeof(values5) / sizeof(values5[0]);
    printf("Maximum value for test case 5: %d\n", knapsack(capacity5, weights5, values5, n5));

    return 0;
}