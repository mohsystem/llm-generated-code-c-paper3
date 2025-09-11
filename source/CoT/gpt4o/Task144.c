#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(const int* arr1, int n1, const int* arr2, int n2) {
    int* mergedArray = (int*)malloc((n1 + n2) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            mergedArray[k++] = arr1[i++];
        } else {
            mergedArray[k++] = arr2[j++];
        }
    }

    while (i < n1) {
        mergedArray[k++] = arr1[i++];
    }

    while (j < n2) {
        mergedArray[k++] = arr2[j++];
    }

    return mergedArray;
}

void printArray(const int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {1, 3, 5};
    int arr2[] = {2, 4, 6};
    int* result1 = mergeSortedArrays(arr1, 3, arr2, 3);
    printArray(result1, 6);
    free(result1);

    int arr3[] = {};
    int arr4[] = {1, 2, 3};
    int* result2 = mergeSortedArrays(arr3, 0, arr4, 3);
    printArray(result2, 3);
    free(result2);

    int arr5[] = {1, 2, 3};
    int arr6[] = {};
    int* result3 = mergeSortedArrays(arr5, 3, arr6, 0);
    printArray(result3, 3);
    free(result3);

    int arr7[] = {1, 3, 5, 7};
    int arr8[] = {2, 4, 6, 8};
    int* result4 = mergeSortedArrays(arr7, 4, arr8, 4);
    printArray(result4, 8);
    free(result4);

    int arr9[] = {1};
    int arr10[] = {2};
    int* result5 = mergeSortedArrays(arr9, 1, arr10, 1);
    printArray(result5, 2);
    free(result5);

    return 0;
}