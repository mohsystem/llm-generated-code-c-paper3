#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int arr[], int n) {
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];

    for (int i = 1; i < n; i++) {
        maxEndingHere = (arr[i] > maxEndingHere + arr[i]) ? arr[i] : maxEndingHere + arr[i];
        maxSoFar = (maxSoFar > maxEndingHere) ? maxSoFar : maxEndingHere;
    }

    return maxSoFar;
}

void main() {
    int testCases[][5] = {
        {1, 2, 3, 4, 5},
        {-1, -2, -3, -4, -5},
        {1, -2, 3, -4, 5},
        {-10, 10, -10, 10},
        {0, 0, 0, 0}
    };

    for (int i = 0; i < 5; i++) {
        int maxSum = maxSubArraySum(testCases[i], 5);
        printf("Maximum subarray sum: %d\n", maxSum);
    }
}