#include <stdio.h>

int findMiddleIndex(int arr[], int size) {
    int totalSum = 0;
    for (int i = 0; i < size; i++) {
        totalSum += arr[i];
    }
    int leftSum = 0;
    for (int i = 0; i < size; i++) {
        if (leftSum == totalSum - leftSum - arr[i]) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}

int main() {
    int testCases[][7] = {
        {1, 2, 3, 4, 3, 2, 1},
        {1, 100, 50, -51, 1, 1},
        {20, 10, -80, 10, 10, 15, 35},
        {1, -1, 1, -1, 1, -1},
        {10, -10}
    };
    int sizes[] = {7, 6, 7, 6, 2};
    for (int i = 0; i < 5; i++) {
        printf("Array: ");
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf(", Index: %d\n", findMiddleIndex(testCases[i], sizes[i]));
    }
    return 0;
}