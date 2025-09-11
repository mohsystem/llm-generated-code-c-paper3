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
        for(int j=0; j<=capacity; j++)
            dp[i][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = (dp[i - 1][w] > (dp[i - 1][w - items[i - 1].weight] + items[i - 1].value)) ?
                           dp[i - 1][w] : (dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
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
    printf("%d\n", knapsack(50, items1, 3)); // Expected: 220

    Item items2[] = {{1, 1}, {3, 4}, {4, 5}, {5, 7}};
    printf("%d\n", knapsack(7, items2, 4)); // Expected: 9

    Item items3[] = {{10, 60}};
    printf("%d\n", knapsack(0, items3, 1)); // Expected: 0

    Item items4[] = {};
    printf("%d\n", knapsack(50, items4, 0)); // Expected: 0

        Item items5[] = {{10, 60}, {20, 100}, {30, 120}};
    printf("%d\n", knapsack(70, items5, 3)); // Expected: 280
    return 0;
}