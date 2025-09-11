#include <stdio.h>
#include <stdlib.h>

int* mergeArrays(int* arr1, int size1, int* arr2, int size2, int* mergedSize) {
    int* mergedArray = (int*)malloc((size1 + size2) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            mergedArray[k++] = arr1[i++];
        } else {
            mergedArray[k++] = arr2[j++];
        }
    }

    while (i < size1) {
        mergedArray[k++] = arr1[i++];
    }

    while (j < size2) {
        mergedArray[k++] = arr2[j++];
    }

    *mergedSize = k;
    return mergedArray;
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int mergedSize;
    int* mergedArray = mergeArrays(arr1, 4, arr2, 4, &mergedSize);
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", mergedArray[i]);
    }
    free(mergedArray);
    return 0;
}