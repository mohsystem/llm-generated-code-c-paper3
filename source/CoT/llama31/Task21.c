// C code
#include <stdio.h>
#include <stdlib.h>

void printArray(int* array, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int* removeSmallest(int* ratings, int size, int* newSize) {
    if (size == 0) return NULL;

    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (ratings[i] < ratings[minIndex]) {
            minIndex = i;
        }
    }

    *newSize = size - 1;
    int* result = (int*)malloc(*newSize * sizeof(int));
    for (int i = 0; i < minIndex; i++) {
        result[i] = ratings[i];
    }
    for (int i = minIndex + 1; i < size; i++) {
        result[i - 1] = ratings[i];
    }
    return result;
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 4, 5},
        {5, 3, 2, 1, 4},
        {2, 2, 1, 2, 1},
        {},
        {10}
    };

    int testCasesSizes[] = {5, 5, 5, 0, 1};

    for (int i = 0; i < 5; ++i) {
        int size = testCasesSizes[i];
        int* ratings = testCases[i];
        int newSize;
        int* result = removeSmallest(ratings, size, &newSize);
        if (result) {
            printArray(result, newSize);
            free(result);
        } else {
            printf("[]\n");
        }
    }

    return 0;
}