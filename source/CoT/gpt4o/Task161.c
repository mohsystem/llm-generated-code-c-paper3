#include <stdio.h>
#include <string.h>

int knapsack(int capacity, int weights[], int values[], int n) {
    int dp[n + 1][capacity + 1];
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w]) ? 
                            values[i - 1] + dp[i - 1][w - weights[i - 1]] : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    
    return dp[n][capacity];
}

int main() {
    int capacity = 50;
    int weights[] = {10, 20, 30};
    int values[] = {60, 100, 120};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("%d\n", knapsack(capacity, weights, values, n));  // 220

    int capacity2 = 10;
    int weights2[] = {1, 4, 3};
    int values2[] = {1500, 3000, 2000};
    int n2 = sizeof(values2) / sizeof(values2[0]);
    
    printf("%d\n", knapsack(capacity2, weights2, values2, n2));  // 3500

    int capacity3 = 7;
    int weights3[] = {1, 3, 4, 5};
    int values3[] = {1, 4, 5, 7};
    int n3 = sizeof(values3) / sizeof(values3[0]);
    
    printf("%d\n", knapsack(capacity3, weights3, values3, n3));  // 9

    int capacity4 = 0;
    int weights4[] = {1, 2};
    int values4[] = {10, 15};
    int n4 = sizeof(values4) / sizeof(values4[0]);
    
    printf("%d\n", knapsack(capacity4, weights4, values4, n4));  // 0

    int capacity5 = 15;
    int weights5[] = {3, 8, 5};
    int values5[] = {40, 10, 50};
    int n5 = sizeof(values5) / sizeof(values5[0]);
    
    printf("%d\n", knapsack(capacity5, weights5, values5, n5));  // 90

    return 0;
}