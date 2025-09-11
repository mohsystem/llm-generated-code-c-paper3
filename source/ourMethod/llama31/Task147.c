#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortDescending(int array[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] < array[j]) {
                swap(&array[i], &array[j]);
            }
        }
    }
}

int findKthLargest(int array[], int size, int k) {
    if (k < 1 || k > size) {
        fprintf(stderr, "k is out of range\n");
        exit(EXIT_FAILURE);
    }

    // Sort the array in descending order
    sortDescending(array, size);

    return array[k - 1];
}

int main() {
    int testCases[][5] = {
        {5, 2, 8, 12, 3},
        {10, 20, 30, 40, 50},
        {100, 200, 300, 400, 500},
        {5, 5, 5, 5, 5},
        {1, 2, 3, 4, 5}
    };
    int kValues[] = {2, 3, 4, 1, 3};

    for (int i = 0; i < 5; i++) {
        int* array = testCases[i];
        int k = kValues[i];
        printf("Array: ");
        for (int j = 0; j < 5; j++) {
            printf("%d ", array[j]);
        }
        printf(", k: %d\n", k);
        printf("Kth largest element: %d\n\n", findKthLargest(array, 5, k));
    }

    return 0;
}