#include <stdio.h>
#include <stdlib.h>

void mergeArrays(int* arr1, int* arr2, int n1, int n2, int* arr3) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            arr3[k++] = arr1[i++];
        } else {
            arr3[k++] = arr2[j++];
        }
    }
    // Copy remaining elements from arr1, if any
    while (i < n1) {
        arr3[k++] = arr1[i++];
    }
    // Copy remaining elements from arr2, if any
    while (j < n2) {
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
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int* arr3 = (int*)malloc((n1 + n2) * sizeof(int));
    mergeArrays(arr1, arr2, n1, n2, arr3);
    printArray(arr3, n1 + n2);
    free(arr3);

    int arr4[] = {5, 8, 9};
    int arr5[] = {4, 7, 8};
    n1 = sizeof(arr4) / sizeof(arr4[0]);
    n2 = sizeof(arr5) / sizeof(arr5[0]);
    arr3 = (int*)malloc((n1 + n2) * sizeof(int));
    mergeArrays(arr4, arr5, n1, n2, arr3);
    printArray(arr3, n1 + n2);
    free(arr3);

    int arr6[] = {1, 2, 3};
    int arr7[] = {4, 5, 6};
    n1 = sizeof(arr6) / sizeof(arr6[0]);
    n2 = sizeof(arr7) / sizeof(arr7[0]);
    arr3 = (int*)malloc((n1 + n2) * sizeof(int));
    mergeArrays(arr6, arr7, n1, n2, arr3);
    printArray(arr3, n1 + n2);
    free(arr3);

    int arr8[] = {4, 5, 6};
    int arr9[] = {1, 2, 3};
    n1 = sizeof(arr8) / sizeof(arr8[0]);
    n2 = sizeof(arr9) / sizeof(arr9[0]);
    arr3 = (int*)malloc((n1 + n2) * sizeof(int));
    mergeArrays(arr8, arr9, n1, n2, arr3);
    printArray(arr3, n1 + n2);
    free(arr3);

    int arr10[] = {1, 3};
    int arr11[] = {2, 4};
    n1 = sizeof(arr10) / sizeof(arr10[0]);
    n2 = sizeof(arr11) / sizeof(arr11[0]);
    arr3 = (int*)malloc((n1 + n2) * sizeof(int));
    mergeArrays(arr10, arr11, n1, n2, arr3);
    printArray(arr3, n1 + n2);
    free(arr3);

    return 0;
}