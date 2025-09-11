#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int* arr1, int len1, int* arr2, int len2) {
    int* mergedArray = (int*)malloc((len1 + len2) * sizeof(int));
    if (!mergedArray) return NULL;
    
    int i = 0, j = 0, k = 0;
    
    while (i < len1 && j < len2) {
        if (arr1[i] < arr2[j]) {
            mergedArray[k++] = arr1[i++];
        } else {
            mergedArray[k++] = arr2[j++];
        }
    }
    
    while (i < len1) {
        mergedArray[k++] = arr1[i++];
    }
    
    while (j < len2) {
        mergedArray[k++] = arr2[j++];
    }
    
    return mergedArray;
}

void printArray(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int* merged = mergeSortedArrays(arr1, len1, arr2, len2);
    printArray(merged, len1 + len2);
    free(merged);
    
    int arr3[] = {};
    int arr4[] = {1, 2, 3};
    int len3 = sizeof(arr3) / sizeof(arr3[0]);
    int len4 = sizeof(arr4) / sizeof(arr4[0]);
    
    merged = mergeSortedArrays(arr3, len3, arr4, len4);
    printArray(merged, len3 + len4);
    free(merged);
    
    int arr5[] = {1, 1, 1};
    int arr6[] = {2, 2, 2};
    int len5 = sizeof(arr5) / sizeof(arr5[0]);
    int len6 = sizeof(arr6) / sizeof(arr6[0]);
    
    merged = mergeSortedArrays(arr5, len5, arr6, len6);
    printArray(merged, len5 + len6);
    free(merged);
    
    int arr7[] = {1, 2, 3};
    int arr8[] = {};
    int len7 = sizeof(arr7) / sizeof(arr7[0]);
    int len8 = sizeof(arr8) / sizeof(arr8[0]);
    
    merged = mergeSortedArrays(arr7, len7, arr8, len8);
    printArray(merged, len7 + len8);
    free(merged);
    
    int arr9[] = {};
    int arr10[] = {};
    int len9 = sizeof(arr9) / sizeof(arr9[0]);
    int len10 = sizeof(arr10) / sizeof(arr10[0]);
    
    merged = mergeSortedArrays(arr9, len9, arr10, len10);
    printArray(merged, len9 + len10);
    free(merged);
    
    return 0;
}