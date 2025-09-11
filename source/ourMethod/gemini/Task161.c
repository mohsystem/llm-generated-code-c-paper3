#include <stdio.h>
#include <stdlib.h>

struct Item {
    int weight;
    int value;
};

int knapsack(int capacity, struct Item items[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w]) ?
                           items[i - 1].value + dp[i - 1][w - items[i - 1].weight] : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
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
    struct Item items1[] = {{10, 60}, {20, 100}, {30, 120}};
    printf("%d\n", knapsack(50, items1, 3)); // Expected: 220

    struct Item items2[] = {{1, 1}, {3, 4}, {4, 5}, {5, 7}};
    printf("%d\n", knapsack(7, items2, 4)); // Expected: 9

    struct Item items3[] = {{10, 1}, {5, 50}};
    printf("%d\n", knapsack(15, items3, 2)); // Expected: 51

    struct Item items4[] = {};
    printf("%d\n", knapsack(10, items4, 0)); // Expected: 0

    struct Item items5[] = {{2, 1}, {3, 2}, {4, 5}, {5, 6}};
    printf("%d\n", knapsack(8, items5, 4)); // Expected: 8

    return 0;
}