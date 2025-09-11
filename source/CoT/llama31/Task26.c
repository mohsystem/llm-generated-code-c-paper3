#include <stdio.h>

int findOdd(int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    int testCases[][10] = {
        {7, 0},
        {0, 0},
        {1, 1, 2, 0},
        {0, 1, 0, 1, 0, 0},
        {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1, 0}
    };
    int sizes[] = {1, 1, 3, 5, 13};

    for (int i = 0; i < 5; i++) {
        printf("Input: ");
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\nOutput: %d\n\n", findOdd(testCases[i], sizes[i]));
    }

    return 0;
}