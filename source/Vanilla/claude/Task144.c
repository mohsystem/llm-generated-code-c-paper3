
#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int arr1[], int n1, int arr2[], int n2, int* resultSize) {
    int* merged = (int*)malloc((n1 + n2) * sizeof(int));
    *resultSize = n1 + n2;
    
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    
    while (i < n1) {
        merged[k++] = arr1[i++];
    }
    
    while (j < n2) {
        merged[k++] = arr2[j++];
    }
    
    return merged;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\\n");
}

int main() {
    int resultSize;
    
    // Test case 1
    int arr1[] = {1, 3, 5};
    int arr2[] = {2, 4, 6};
    printf("Test 1: ");
    int* result = mergeSortedArrays(arr1, 3, arr2, 3, &resultSize);
    printArray(result, resultSize);
    free(result);
    
    // Test case 2
    int arr3[] = {1, 2, 3, 4};
    int arr4[] = {5, 6, 7, 8};
    printf("Test 2: ");
    result = mergeSortedArrays(arr3, 4, arr4, 4, &resultSize);
    printArray(result, resultSize);
    free(result);
    
    // Test case 3
    int arr5[] = {1, 3, 5, 7};
    int arr6[] = {2, 4};
    printf("Test 3: ");
    result = mergeSortedArrays(arr5, 4, arr6, 2, &resultSize);
    printArray(result, resultSize);
    free(result);
    
    // Test case 4
    int arr7[] = {};
    int arr8[] = {1, 2, 3};
    printf("Test 4: ");
    result = mergeSortedArrays(arr7, 0, arr8, 3, &resultSize);
    printArray(result, resultSize);
    free(result);
    
    // Test case 5
    int arr9[] = {1, 1, 2, 3};
    int arr10[] = {1, 2, 2, 4};
    printf("Test 5: ");
    result = mergeSortedArrays(arr9, 4, arr10, 4, &resultSize);
    printArray(result, resultSize);
    free(result);
    
    return 0;
}
