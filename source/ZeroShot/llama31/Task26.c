#include <stdio.h>

int findOddOccurrence(int arr[], int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = res ^ arr[i];
    }
    return res;
}

int main() {
    int testCases[][10] = {
        {7},
        {0},
        {1, 1, 2},
        {0, 1, 0, 1, 0},
        {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1}
    };
    int testCaseSizes[] = {1, 1, 3, 5, 13};

    for (int i = 0; i < 5; i++) {
        printf("Input: ");
        for (int j = 0; j < testCaseSizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\nOutput: %d\n\n", findOddOccurrence(testCases[i], testCaseSizes[i]));
    }

    return 0;
}