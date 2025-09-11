#include <stdio.h>
#include <stdlib.h>

void removeSmallest(int* ratings, int length, int** result, int* resultLength) {
    if (length == 0) {
        *result = NULL;
        *resultLength = 0;
        return;
    }

    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (ratings[i] < ratings[minIndex]) {
            minIndex = i;
        }
    }

    *result = (int*)malloc((length - 1) * sizeof(int));
    *resultLength = length - 1;

    int j = 0;
    for (int i = 0; i < length; i++) {
        if (i != minIndex) {
            (*result)[j++] = ratings[i];
        }
    }
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 4, 5},
        {5, 3, 2, 1, 4},
        {2, 2, 1, 2, 1},
        {}
    };
    int testCasesLengths[] = {5, 5, 5, 0};

    for (int i = 0; i < 4; i++) {
        int* result;
        int resultLength;
        removeSmallest(testCases[i], testCasesLengths[i], &result, &resultLength);

        for (int j = 0; j < resultLength; j++) {
            printf("%d ", result[j]);
        }
        printf("\n");

        free(result);
    }

    return 0;
}