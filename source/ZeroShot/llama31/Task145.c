#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int arr[], int n) {
    int bestSum = INT_MIN;
    int currentSum = 0;
    for (int i = 0; i < n; i++) {
        currentSum = (arr[i] > currentSum + arr[i]) ? arr[i] : currentSum + arr[i];
        bestSum = (bestSum > currentSum) ? bestSum : currentSum;
    }
    return bestSum;
}

int main() {
    int testCases[][5] = {
        {-2, 1, -3, 4, -1},
        {-2, -5, 6, -2, -3},
        {1, 2, 3, 4, 5},
        {-1, -2, -3, -4, -5},
        {0, 0, 0, 0, 0}
    };
    int expectedResults[] = {6, 7, 15, -1, 0};

    for (int i = 0; i < 5; i++) {
        printf("Maximum contiguous sum is: %d\n", maxSubArraySum(testCases[i], 5));
    }

    return 0;
}