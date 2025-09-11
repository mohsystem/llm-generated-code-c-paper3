#include <stdio.h>
#include <stdlib.h>

void removeSmallest(int* arr, int n, int** result, int* resultSize) {
    if (n == 0) {
        *result = NULL;
        *resultSize = 0;
        return;
    }

    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }

    *resultSize = n - 1;
    *result = (int*)malloc((*resultSize) * sizeof(int));
    for (int i = 0; i < minIndex; i++) {
        (*result)[i] = arr[i];
    }
    for (int i = minIndex + 1; i < n; i++) {
        (*result)[i - 1] = arr[i];
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 4, 5},
        {5, 3, 2, 1, 4},
        {2, 2, 1, 2, 1},
        {},
        {10}
    };

    int sizes[] = {5, 5, 5, 0, 1};

    for (int i = 0; i < 5; i++) {
        int* result;
        int resultSize;
        removeSmallest(testCases[i], sizes[i], &result, &resultSize);
        printArray(result, resultSize);
        free(result);
    }

    return 0;
}