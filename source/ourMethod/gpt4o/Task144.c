#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int* arr1, int size1, int* arr2, int size2, int* mergedSize) {
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
    int arr1[] = {1, 3, 5};
    int arr2[] = {2, 4, 6};
    int arr3[] = {10, 20, 30};
    int arr4[] = {5, 15, 25};
    int arr5[] = {100, 200};
    int arr6[] = {50, 150};
    int mergedSize;

    // Test cases
    int* result1 = mergeSortedArrays(arr1, 3, arr2, 3, &mergedSize);
    int* result2 = mergeSortedArrays(arr3, 3, arr4, 3, &mergedSize);
    int* result3 = mergeSortedArrays(arr5, 2, arr6, 2, &mergedSize);
    int* result4 = mergeSortedArrays(arr1, 3, arr3, 3, &mergedSize);
    int* result5 = mergeSortedArrays(arr4, 3, arr6, 2, &mergedSize);

    // Output results
    for (int i = 0; i < mergedSize; i++) printf("%d ", result1[i]);
    printf("\n");
    for (int i = 0; i < mergedSize; i++) printf("%d ", result2[i]);
    printf("\n");
    for (int i = 0; i < mergedSize; i++) printf("%d ", result3[i]);
    printf("\n");
    for (int i = 0; i < mergedSize; i++) printf("%d ", result4[i]);
    printf("\n");
    for (int i = 0; i < mergedSize; i++) printf("%d ", result5[i]);
    printf("\n");

    // Free allocated memory
    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}