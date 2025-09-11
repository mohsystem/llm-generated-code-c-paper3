#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int* arr1, int size1, int* arr2, int size2, int* mergedSize) {
    int* mergedArray = (int*)malloc((size1 + size2) * sizeof(int));
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            mergedArray[k] = arr1[i];
            i++;
        } else {
            mergedArray[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < size1) {
        mergedArray[k] = arr1[i];
        i++;
        k++;
    }

    while (j < size2) {
        mergedArray[k] = arr2[j];
        j++;
        k++;
    }

    *mergedSize = size1 + size2;
    return mergedArray;
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int arr2[] = {2, 4, 6, 8};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int mergedSize;
    int* mergedArray = mergeSortedArrays(arr1, size1, arr2, size2, &mergedSize);
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", mergedArray[i]);
    }
    printf("\n");
    free(mergedArray);

    int arr3[] = {1, 3, 5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int arr4[] = {2, 4, 6, 8, 10};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    mergedArray = mergeSortedArrays(arr3, size3, arr4, size4, &mergedSize);
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", mergedArray[i]);
    }
    printf("\n");
    free(mergedArray);

    int arr5[] = {1, 2, 3};
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    int arr6[] = {4, 5, 6};
    int size6 = sizeof(arr6) / sizeof(arr6[0]);
    mergedArray = mergeSortedArrays(arr5, size5, arr6, size6, &mergedSize);
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", mergedArray[i]);
    }
    printf("\n");
    free(mergedArray);

    int arr7[] = {};
    int size7 = sizeof(arr7) / sizeof(arr7[0]);
    int arr8[] = {1, 2, 3};
    int size8 = sizeof(arr8) / sizeof(arr8[0]);
    mergedArray = mergeSortedArrays(arr7, size7, arr8, size8, &mergedSize);
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", mergedArray[i]);
    }
    printf("\n");
    free(mergedArray);

    int arr9[] = {1, 2, 3};
    int size9 = sizeof(arr9) / sizeof(arr9[0]);
    int arr10[] = {};
    int size10 = sizeof(arr10) / sizeof(arr10[0]);
    mergedArray = mergeSortedArrays(arr9, size9, arr10, size10, &mergedSize);
    for (int i = 0; i < mergedSize; i++) {
        printf("%d ", mergedArray[i]);
    }
    printf("\n");
    free(mergedArray);

    return 0;
}