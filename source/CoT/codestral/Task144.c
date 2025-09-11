#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int* arr1, int size1, int* arr2, int size2, int* resultSize) {
    int* result = (int*)malloc((size1 + size2) * sizeof(int));
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    while (i < size1) {
        result[k++] = arr1[i++];
    }
    while (j < size2) {
        result[k++] = arr2[j++];
    }
    *resultSize = size1 + size2;
    return result;
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int resultSize;
    int* merged = mergeSortedArrays(arr1, 4, arr2, 4, &resultSize);
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", merged[i]);
    }
    free(merged);
    return 0;
}