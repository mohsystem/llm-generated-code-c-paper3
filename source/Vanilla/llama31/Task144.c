#include <stdio.h>
#include <stdlib.h>

void mergeArrays(int* arr1, int* arr2, int m, int n, int* arr3) {
    int i = 0, j = 0, k = 0;
    while (i < m && j < n) {
        if (arr1[i] < arr2[j]) {
            arr3[k++] = arr1[i++];
        } else {
            arr3[k++] = arr2[j++];
        }
    }
    // Copy remaining elements from arr1, if any
    while (i < m) {
        arr3[k++] = arr1[i++];
    }
    // Copy remaining elements from arr2, if any
    while (j < n) {
        arr3[k++] = arr2[j++];
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Test cases
    int testCases[][2][5] = {
        {{1, 3, 4, 5}, {2, 4, 6, 8}},
        {{5, 8, 9}, {4, 7, 8}},
        {{1, 2}, {3, 4}},
        {{1}, {2, 3}},
        {{1, 2, 3}, {4, 5, 6}}
    };

    for (int i = 0; i < 5; i++) {
        int m = sizeof(testCases[i][0]) / sizeof(testCases[i][0][0]);
        int n = sizeof(testCases[i][1]) / sizeof(testCases[i][1][0]);
        int* arr3 = (int*)malloc((m + n) * sizeof(int));
        mergeArrays(testCases[i][0], testCases[i][1], m, n, arr3);
        printf("Array 1: ");
        printArray(testCases[i][0], m);
        printf("Array 2: ");
        printArray(testCases[i][1], n);
        printf("Merged Array: ");
        printArray(arr3, m + n);
        printf("\n");
        free(arr3);
    }

    return 0;
}