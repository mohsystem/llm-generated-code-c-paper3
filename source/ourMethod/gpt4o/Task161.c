#include <stdio.h>

int knapsack(int capacity, int weights[], int values[], int n) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                int includeItem = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                int excludeItem = dp[i - 1][w];
                dp[i][w] = (includeItem > excludeItem) ? includeItem : excludeItem;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int weights1[] = {10, 20, 30};
    int values1[] = {60, 100, 120};
    int n1 = sizeof(weights1) / sizeof(weights1[0]);
    printf("%d\n", knapsack(50, weights1, values1, n1)); // 220

    int weights2[] = {5, 4, 6};
    int values2[] = {10, 40, 30};
    int n2 = sizeof(weights2) / sizeof(weights2[0]);
    printf("%d\n", knapsack(10, weights2, values2, n2)); // 40

    int weights3[] = {1, 2, 3};
    int values3[] = {6, 10, 12};
    int n3 = sizeof(weights3) / sizeof(weights3[0]);
    printf("%d\n", knapsack(5, weights3, values3, n3)); // 22

    int weights4[] = {1, 2, 3};
    int values4[] = {6, 10, 12};
    int n4 = sizeof(weights4) / sizeof(weights4[0]);
    printf("%d\n", knapsack(0, weights4, values4, n4)); // 0

    int weights5[] = {2, 3, 4, 5};
    int values5[] = {3, 4, 5, 6};
    int n5 = sizeof(weights5) / sizeof(weights5[0]);
    printf("%d\n", knapsack(7, weights5, values5, n5)); // 9

    return 0;
}