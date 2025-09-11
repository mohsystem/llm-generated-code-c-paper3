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
    *resultLength = length - 1;
    *result = (int*)malloc((*resultLength) * sizeof(int));
    for (int i = 0; i < minIndex; i++) {
        (*result)[i] = ratings[i];
    }
    for (int i = minIndex + 1; i < length; i++) {
        (*result)[i - 1] = ratings[i];
    }
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 4, 5},
        {5, 3, 2, 1, 4},
        {2, 2, 1, 2, 1},
        {},
        {1}
    };
    int lengths[] = {5, 5, 5, 0, 1};
    for (int i = 0; i < 5; i++) {
        int* result;
        int resultLength;
        removeSmallest(testCases[i], lengths[i], &result, &resultLength);
        for (int j = 0; j < resultLength; j++) {
            printf("%d ", result[j]);
        }
        free(result);
        printf("\n");
    }
    return 0;
}