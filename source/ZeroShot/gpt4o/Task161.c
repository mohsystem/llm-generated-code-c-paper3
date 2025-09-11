#include <stdio.h>

int knapsack(int capacity, int weights[], int values[], int n) {
    int dp[n + 1][capacity + 1];
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                int include = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                int exclude = dp[i - 1][w];
                dp[i][w] = include > exclude ? include : exclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

int main() {
    int weights1[] = {1, 2, 3, 2, 2};
    int values1[] = {8, 4, 0, 5, 3};
    int capacity1 = 4;
    int n1 = sizeof(weights1) / sizeof(weights1[0]);
    printf("%d\n", knapsack(capacity1, weights1, values1, n1)); // Output: 13

    int weights2[] = {1, 2, 3};
    int values2[] = {6, 10, 12};
    int capacity2 = 5;
    int n2 = sizeof(weights2) / sizeof(weights2[0]);
    printf("%d\n", knapsack(capacity2, weights2, values2, n2)); // Output: 22

    int weights3[] = {4, 5, 1};
    int values3[] = {1, 2, 3};
    int capacity3 = 4;
    int n3 = sizeof(weights3) / sizeof(weights3[0]);
    printf("%d\n", knapsack(capacity3, weights3, values3, n3)); // Output: 3

    int weights4[] = {2, 3, 4, 5};
    int values4[] = {3, 4, 5, 6};
    int capacity4 = 5;
    int n4 = sizeof(weights4) / sizeof(weights4[0]);
    printf("%d\n", knapsack(capacity4, weights4, values4, n4)); // Output: 7

    int weights5[] = {1, 3, 4, 5};
    int values5[] = {1, 4, 5, 7};
    int capacity5 = 7;
    int n5 = sizeof(weights5) / sizeof(weights5[0]);
    printf("%d\n", knapsack(capacity5, weights5, values5, n5)); // Output: 9

    return 0;
}