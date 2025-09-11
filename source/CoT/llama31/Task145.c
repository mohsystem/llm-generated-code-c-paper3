#include <stdio.h>
#include <stdlib.h>

int maxSubArraySum(int arr[], int n) {
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];
    for (int i = 1; i < n; i++) {
        maxEndingHere = (arr[i] > maxEndingHere + arr[i]) ? arr[i] : maxEndingHere + arr[i];
        maxSoFar = (maxSoFar > maxEndingHere) ? maxSoFar : maxEndingHere;
    }
    return maxSoFar;
}

int main() {
    int testCases[][8] = {
        { -2, -3, 4, -1, -2, 1, 5, -3 },
        { 1, 2, 3, 4, 5, 0, 0, 0 },
        { -1, -2, -3, -4, -5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, -1, 1, -1, 1, 0, 0, 0 }
    };
    int sizes[] = {8, 5, 5, 5, 5};

    for (int i = 0; i < 5; i++) {
        printf("Maximum subarray sum: %d\n", maxSubArraySum(testCases[i], sizes[i]));
    }

    return 0;
}