#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int* arr1, int n1, int* arr2, int n2, int* mergedArraySize) {
    int* mergedArray = (int*)malloc((n1 + n2) * sizeof(int));
    if (mergedArray == NULL) {
        *mergedArraySize = 0;
        return NULL; // Return NULL to indicate memory allocation failure
    }
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
    *mergedArraySize = k;
    return mergedArray;
}

int main() {
    int arr1_1[] = {1, 3, 5, 7};
    int arr2_1[] = {2, 4, 6, 8};
    int n1_1 = sizeof(arr1_1) / sizeof(arr1_1[0]);
    int n2_1 = sizeof(arr2_1) / sizeof(arr2_1[0]);
    int mergedSize1;
    int* merged1 = mergeSortedArrays(arr1_1, n1_1, arr2_1, n2_1, &mergedSize1);
    for (int i = 0; i < mergedSize1; i++) printf("%d ", merged1[i]);
    printf("\n");
    free(merged1);

    int arr1_2[] = {1, 2, 3};
    int arr2_2[] = {4, 5, 6};
    int n1_2 = sizeof(arr1_2) / sizeof(arr1_2[0]);
    int n2_2 = sizeof(arr2_2) / sizeof(arr2_2[0]);
    int mergedSize2;
    int* merged2 = mergeSortedArrays(arr1_2, n1_2, arr2_2, n2_2, &mergedSize2);
    for (int i = 0; i < mergedSize2; i++) printf("%d ", merged2[i]);
    printf("\n");
    free(merged2);

    int arr1_3[] = {};
    int arr2_3[] = {1, 2, 3};
    int n1_3 = sizeof(arr1_3) / sizeof(arr1_3[0]);
    int n2_3 = sizeof(arr2_3) / sizeof(arr2_3[0]);
    int mergedSize3;
    int *merged3 = mergeSortedArrays(arr1_3, n1_3, arr2_3, n2_3, &mergedSize3);
    for (int i = 0; i < mergedSize3; i++) printf("%d ", merged3[i]);
    printf("\n");
    free(merged3);

    int arr1_4[] = {1, 2, 3};
    int arr2_4[] = {};
    int n1_4 = sizeof(arr1_4) / sizeof(arr1_4[0]);
    int n2_4 = sizeof(arr2_4) / sizeof(arr2_4[0]);
    int mergedSize4;
    int* merged4 = mergeSortedArrays(arr1_4, n1_4, arr2_4, n2_4, &mergedSize4);
    for (int i = 0; i < mergedSize4; i++) printf("%d ", merged4[i]);
    printf("\n");
    free(merged4);


    int arr1_5[] = {1, 3, 5};
    int arr2_5[] = {2, 4, 6, 8, 10};
    int n1_5 = sizeof(arr1_5) / sizeof(arr1_5[0]);
    int n2_5 = sizeof(arr2_5) / sizeof(arr2_5[0]);
    int mergedSize5;
    int* merged5 = mergeSortedArrays(arr1_5, n1_5, arr2_5, n2_5, &mergedSize5);
    for (int i = 0; i < mergedSize5; i++) printf("%d ", merged5[i]);
    printf("\n");
    free(merged5);

    return 0;
}