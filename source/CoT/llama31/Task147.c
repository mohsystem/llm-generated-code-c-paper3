#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortDescending(int* array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] < array[j]) {
                swap(&array[i], &array[j]);
            }
        }
    }
}

int findKthLargest(int* array, int size, int k) {
    sortDescending(array, size);
    return array[k - 1];
}

int main() {
    int testCases[][7] = {
        {3, 2, 1, 5, 6, 4, 2},
        {1, 2, 3, 4, 5, 3},
        {10, 20, 30, 40, 50, 1},
        {5, 5, 5, 5, 5, 2},
        {1, 1}
    };

    for (int i = 0; i < 5; ++i) {
        int arraySize = sizeof(testCases[i]) / sizeof(testCases[i][0]) - 1;
        int* array = (int*)malloc(arraySize * sizeof(int));
        for (int j = 0; j < arraySize; ++j) {
            array[j] = testCases[i][j];
        }
        int k = testCases[i][arraySize];
        printf("Array: ");
        for (int j = 0; j < arraySize; ++j) {
            printf("%d ", array[j]);
        }
        printf(", k: %d\n", k);
        printf("Kth largest element: %d\n\n", findKthLargest(array, arraySize, k));
        free(array);
    }
    return 0;
}