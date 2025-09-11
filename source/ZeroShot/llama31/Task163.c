#include <stdio.h>
#include <stdlib.h>

int longestRun(int* arr, int size) {
    if (size == 0) return 0;
    int maxRun = 1;
    int currentRun = 1;
    for (int i = 1; i < size; i++) {
        if (abs(arr[i] - arr[i - 1]) == 1) {
            currentRun++;
        } else {
            if (currentRun > maxRun) {
                maxRun = currentRun;
            }
            currentRun = 1;
        }
    }
    return (maxRun > currentRun) ? maxRun : currentRun;
}

int main() {
    int testCases[][10] = {{1, 2, 3, 5, 6, 7, 8, 9, 0}, {1, 2, 3, 10, 11, 15, 0}, {5, 4, 2, 1, 0}, {3, 5, 7, 10, 15, 0}, {0}};
    int sizes[] = {9, 6, 4, 5, 0};
    for (int i = 0; i < 5; i++) {
        printf("%d\n", longestRun(testCases[i], sizes[i]));
    }
    return 0;
}