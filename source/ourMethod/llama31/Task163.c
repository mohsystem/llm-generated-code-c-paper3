#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int longestRun(int* arr, int size) {
    if (size == 0) return 0;
    int maxRun = 1;
    int currentRun = 1;
    for (int i = 1; i < size; i++) {
        if (abs(arr[i] - arr[i - 1]) == 1) {
            currentRun++;
        } else {
            maxRun = (maxRun > currentRun) ? maxRun : currentRun;
            currentRun = 1;
        }
    }
    return (maxRun > currentRun) ? maxRun : currentRun;
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 5, 6, 7, 8, 9},
        {1, 2, 3, 10, 11, 15},
        {5, 4, 2, 1},
        {3, 5, 7, 10, 15},
        {}
    };
    int sizes[] = {8, 5, 4, 5, 0};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", longestRun(testCases[i], sizes[i]));
    }

    return 0;
}