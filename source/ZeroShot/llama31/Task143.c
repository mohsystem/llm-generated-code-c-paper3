#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int array[], int size) {
    for (int step = 0; step < size - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < size; i++) {
            if (array[i] < array[min_idx]) {
                min_idx = i;
            }
        }
        // Swap the found minimum element with the first element of the unsorted part
        swap(&array[step], &array[min_idx]);
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int testCases[][7] = {
        {20, 12, 10, 15, 2},
        {5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5},
        {-2, 45, 0, 11, -9},
        {64, 34, 25, 12, 22, 11, 90}
    };
    int sizes[] = {5, 5, 5, 5, 7};

    for (int i = 0; i < 5; i++) {
        selectionSort(testCases[i], sizes[i]);
        printf("Sorted Array: ");
        printArray(testCases[i], sizes[i]);
    }

    return 0;
}