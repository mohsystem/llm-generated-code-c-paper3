#include<stdio.h>
#define max(a, b) (a > b) ? a : b

int knapSack(int capacity, int weights[], int values[], int n) {
    if (n == 0 || capacity == 0)
        return 0;
    if (weights[n - 1] > capacity)
        return knapSack(capacity, weights, values, n - 1);
    else
        return max(values[n - 1] + knapSack(capacity - weights[n - 1], weights, values, n - 1), knapSack(capacity, weights, values, n - 1));
}

int main() {
    int weights[] = {10, 20, 30};
    int values[] = {60, 100, 120};
    int capacity = 50;
    int n = sizeof(values) / sizeof(values[0]);
    printf("%d", knapSack(capacity, weights, values, n));
    return 0;
}