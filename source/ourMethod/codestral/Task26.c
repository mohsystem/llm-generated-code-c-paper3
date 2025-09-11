#include <stdio.h>

int findOdd(const int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; ++i) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    int testCases[][9] = {
        {7},
        {0},
        {1, 1, 2},
        {0, 1, 0, 1, 0},
        {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1}
    };
    int testCaseSizes[] = {1, 1, 3, 5, 13};

    for (int i = 0; i < 5; ++i) {
        printf("Array: ");
        for (int j = 0; j < testCaseSizes[i]; ++j) {
            printf("%d ", testCases[i][j]);
        }
        printf(", Result: %d\n", findOdd(testCases[i], testCaseSizes[i]));
    }

    return 0;
}