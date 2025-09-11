#include <stdio.h>

int findMiddleIndex(int arr[], int n) {
    if (n == 0) {
        return -1;
    }
    int leftSum = 0;
    int rightSum = 0;
    for (int i = 0; i < n; ++i) {
        rightSum += arr[i];
    }
    for (int i = 0; i < n; ++i) {
        rightSum -= arr[i];
        if (leftSum == rightSum) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}

int main() {
    int testCases[][7] = {
        {1, 2, 3, 4, 3, 2, 1},
        {1, 100, 50, -51, 1, 1, 0},
        {20, 10, -80, 10, 10, 15, 35},
        {},
        {1}
    };
    int testCaseSizes[] = {7, 6, 7, 0, 1};
    for (int i = 0; i < 5; ++i) {
        printf("Array: ");
        for (int j = 0; j < testCaseSizes[i]; ++j) {
            printf("%d ", testCases[i][j]);
        }
        printf("\nIndex: %d\n", findMiddleIndex(testCases[i], testCaseSizes[i]));
    }
    return 0;
}