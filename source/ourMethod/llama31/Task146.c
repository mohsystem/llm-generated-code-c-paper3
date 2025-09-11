#include <stdio.h>

int findMissingNumber(int arr[], int size) {
    int n = size + 1;
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    for (int i = 0; i < size; ++i) {
        actualSum += arr[i];
    }
    return expectedSum - actualSum;
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 5, 0},
        {1, 2, 4, 5, 0},
        {1, 3, 4, 5, 0},
        {2, 3, 4, 5, 0},
        {1, 2, 3, 4, 0}
    };

    for (int i = 0; i < 5; ++i) {
        int size = sizeof(testCases[i]) / sizeof(testCases[i][0]) - 1; // exclude the last 0
        printf("Missing number in array: %d\n", findMissingNumber(testCases[i], size));
    }

    return 0;
}