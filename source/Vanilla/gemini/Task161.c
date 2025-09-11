#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
} Item;

int knapsack(int capacity, Item items[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = (dp[i - 1][w - items[i - 1].weight] + items[i - 1].value > dp[i - 1][w]) ? 
                           (dp[i - 1][w - items[i - 1].weight] + items[i - 1].value) : dp[i - 1][w];
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
    Item items1[] = {{10, 60}, {20, 100}, {30, 120}};
    printf("%d\n", knapsack(50, items1, 3)); // Output: 220

    Item items2[] = {{1, 1}, {3, 4}, {4, 5}, {5, 7}};
    printf("%d\n", knapsack(7, items2, 4)); // Output: 9

    Item items3[] = {{10, 1}, {20, 2}, {30, 3}};
    printf("%d\n", knapsack(10, items3, 3));//1

    Item items4[] = {{1, 2}, {2, 5}};
    printf("%d\n", knapsack(3, items4, 2)); //7

    Item items5[] = {{5, 10}, {10, 20}};
    printf("%d\n", knapsack(15, items5, 2));//30

    return 0;
}