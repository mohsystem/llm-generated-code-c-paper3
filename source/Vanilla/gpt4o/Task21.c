#include <stdio.h>
#include <limits.h>

void removeSmallest(int* numbers, int length, int* result, int* resultLength) {
    if (length == 0) {
        *resultLength = 0;
        return;
    }
    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (numbers[i] < numbers[minIndex]) {
            minIndex = i;
        }
    }
    *resultLength = 0;
    for (int i = 0; i < length; i++) {
        if (i != minIndex) {
            result[(*resultLength)++] = numbers[i];
        }
    }
}

void printArray(int* array, int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", array[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int result[5];
    int resultLength;

    int numbers1[] = {1, 2, 3, 4, 5};
    removeSmallest(numbers1, 5, result, &resultLength);
    printArray(result, resultLength);

    int numbers2[] = {5, 3, 2, 1, 4};
    removeSmallest(numbers2, 5, result, &resultLength);
    printArray(result, resultLength);

    int numbers3[] = {2, 2, 1, 2, 1};
    removeSmallest(numbers3, 5, result, &resultLength);
    printArray(result, resultLength);

    int numbers4[] = {1};
    removeSmallest(numbers4, 1, result, &resultLength);
    printArray(result, resultLength);

    int numbers5[] = {};
    removeSmallest(numbers5, 0, result, &resultLength);
    printArray(result, resultLength);

    return 0;
}