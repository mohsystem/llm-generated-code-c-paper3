#include <stdio.h>
#include <stdlib.h>

int longestRun(int* arr, int size) {
    if (size == 0) return 0;
    if (size == 1) return 1;

    int maxLength = 1;
    int currentLength = 1;

    for (int i = 1; i < size; i++) {
        if (abs(arr[i] - arr[i - 1]) == 1) {
            currentLength++;
        } else {
            maxLength = (maxLength > currentLength) ? maxLength : currentLength;
            currentLength = 1;
        }
    }

    return (maxLength > currentLength) ? maxLength : currentLength;
}

void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

int main() {
    int testCases[][5] = {
        {1, 2, 3, 5, 6, 7, 8, 9},
        {1, 2, 3, 10, 11, 15},
        {5, 4, 2, 1},
        {3, 5, 7, 10, 15},
        {1, 3, 5, 7, 9}
    };
    int sizes[] = {9, 6, 4, 5, 5};

    for (int i = 0; i < 5; i++) {
        printf("longestRun(");
        printArray(testCases[i], sizes[i]);
        printf(") ➞ %d\n", longestRun(testCases[i], sizes[i]));
    }

    return 0;
}