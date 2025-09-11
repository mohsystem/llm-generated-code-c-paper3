#include <stdio.h>
#include <stdlib.h>

void sortArray(int* array, int size) {
    if (array == NULL || size <= 0) return;
    
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int testCases[5][6] = {
        {5, 2, 9, 1, 5, 6},
        {3, 0, -2, 10, 4, 0},
        {0},
        {1},
        {-1, -10, 2, 3, 0, 0}
    };
    int sizes[] = {6, 5, 0, 1, 5};

    for (int i = 0; i < 5; ++i) {
        sortArray(testCases[i], sizes[i]);
        printArray(testCases[i], sizes[i]);
    }
    return 0;
}