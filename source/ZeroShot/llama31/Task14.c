#include <stdio.h>

int findMiddleIndex(int arr[], int length) {
    if (length == 0) {
        return -1;
    }
    int totalSum = 0;
    for (int i = 0; i < length; ++i) {
        totalSum += arr[i];
    }
    int leftSum = 0;
    for (int i = 0; i < length; ++i) {
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
        {},
        {1}
    };
    int lengths[] = {7, 6, 7, 0, 1};
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", findMiddleIndex(testCases[i], lengths[i]));
    }
    return 0;
}