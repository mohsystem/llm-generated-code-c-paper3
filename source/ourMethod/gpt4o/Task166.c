#include <stdio.h>
#include <stdlib.h>

void posNegSort(int* arr, int size) {
    int* posNums = (int*)malloc(size * sizeof(int));
    int posCount = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            posNums[posCount++] = arr[i];
        }
    }

    // Sort positive numbers
    for (int i = 0; i < posCount - 1; i++) {
        for (int j = i + 1; j < posCount; j++) {
            if (posNums[i] > posNums[j]) {
                int temp = posNums[i];
                posNums[i] = posNums[j];
                posNums[j] = temp;
            }
        }
    }

    int posIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            arr[i] = posNums[posIndex++];
        }
    }

    free(posNums);
}

void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int testCases[][7] = {
        {6, 3, -2, 5, -8, 2, -2},
        {6, 5, 4, -1, 3, 2, -1, 1},
        {-5, -5, -5, -5, 7, -5},
        {},
        {3, -1, -2, 2, 1}
    };
    int testSizes[] = {7, 8, 6, 0, 5};

    for (int i = 0; i < 5; i++) {
        posNegSort(testCases[i], testSizes[i]);
        printArray(testCases[i], testSizes[i]);
    }

    return 0;
}