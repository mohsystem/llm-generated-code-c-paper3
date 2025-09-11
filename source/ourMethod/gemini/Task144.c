#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int* arr1, int n1, int* arr2, int n2, int* mergedSize) {
    int* mergedArr = (int*)malloc((n1 + n2) * sizeof(int));
    if (mergedArr == NULL) {
        *mergedSize = 0;
        return NULL; 
    }

    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            mergedArr[k++] = arr1[i++];
        } else {
            mergedArr[k++] = arr2[j++];
        }
    }

    while (i < n1) {
        mergedArr[k++] = arr1[i++];
    }

    while (j < n2) {
        mergedArr[k++] = arr2[j++];
    }

    *mergedSize = k;
    return mergedArr;
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int arr2[] = {2, 4, 6, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int mergedSize;

    int *mergedArr = mergeSortedArrays(arr1, n1, arr2, n2, &mergedSize);
    if (mergedArr != NULL) {
        for (int i = 0; i < mergedSize; i++) {
            printf("%d ", mergedArr[i]);
        }
        printf("\n");
        free(mergedArr);
    }


    int arr3[] = {1, 2, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int arr4[] = {4, 5, 6};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);


    mergedArr = mergeSortedArrays(arr3, n3, arr4, n4, &mergedSize);
     if (mergedArr != NULL) {
        for (int i = 0; i < mergedSize; i++) {
            printf("%d ", mergedArr[i]);
        }
        printf("\n");
        free(mergedArr);
    }



    int arr5[] = {};
    int n5 = 0;
    int arr6[] = {1, 2, 3};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);

    mergedArr = mergeSortedArrays(arr5, n5, arr6, n6, &mergedSize);
    if (mergedArr != NULL) {
        for (int i = 0; i < mergedSize; i++) {
            printf("%d ", mergedArr[i]);
        }
        printf("\n");
        free(mergedArr);
    }



    int arr7[] = {1, 2, 3};
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    int arr8[] = {};
    int n8 = 0;

    mergedArr = mergeSortedArrays(arr7, n7, arr8, n8, &mergedSize);
    if (mergedArr != NULL) {
        for (int i = 0; i < mergedSize; i++) {
            printf("%d ", mergedArr[i]);
        }
        printf("\n");
        free(mergedArr);
    }



    int arr9[] = {1, 3, 5};
    int n9 = sizeof(arr9) / sizeof(arr9[0]);
    int arr10[] = {2, 4, 6, 8, 10};
    int n10 = sizeof(arr10) / sizeof(arr10[0]);

    mergedArr = mergeSortedArrays(arr9, n9, arr10, n10, &mergedSize);
    if (mergedArr != NULL) {
        for (int i = 0; i < mergedSize; i++) {
            printf("%d ", mergedArr[i]);
        }
        printf("\n");
        free(mergedArr);
    }

    return 0;
}