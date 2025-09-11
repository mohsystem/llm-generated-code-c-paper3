#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(const int* numbers, int length, int* newLength) {
    if (length == 0) {
        *newLength = 0;
        return NULL;
    }

    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (numbers[i] < numbers[minIndex]) {
            minIndex = i;
        }
    }

    *newLength = length - 1;
    int* result = (int*)malloc((*newLength) * sizeof(int));
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    
    return result;
}

void printArray(const int* arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int testCases[5][5] = {
        {1, 2, 3, 4, 5},
        {5, 3, 2, 1, 4},
        {2, 2, 1, 2, 1},
        {},
        {1}
    };

    int testCaseLengths[5] = {5, 5, 5, 0, 1};

    for (int i = 0; i < 5; i++) {
        int newLength;
        int* result = removeSmallest(testCases[i], testCaseLengths[i], &newLength);
        printArray(result, newLength);
        free(result);
    }

    return 0;
}