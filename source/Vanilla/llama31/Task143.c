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
    int testCases[][5] = {
        {-2, 45, 0, 11, -9},
        {5, 2, 8, 7, 1},
        {10, 9, 8, 7, 6},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1}
    };

    for (int i = 0; i < 5; i++) {
        selectionSort(testCases[i], 5);
        printf("Sorted Array: ");
        printArray(testCases[i], 5);
    }

    return 0;
}