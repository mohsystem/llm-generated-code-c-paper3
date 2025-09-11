
#include <stdio.h>
#include <stdlib.h>

int* mergeArrays(const int* arr1, int size1, const int* arr2, int size2, int* resultSize) {
    if (arr1 == NULL || arr2 == NULL || resultSize == NULL) {
        return NULL;
    }
    
    int* merged = (int*)malloc((size1 + size2) * sizeof(int));
    if (merged == NULL) {
        return NULL;
    }
    
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    
    while (i < size1) {
        merged[k++] = arr1[i++];
    }
    
    while (j < size2) {
        merged[k++] = arr2[j++];
    }
    
    *resultSize = size1 + size2;
    return merged;
}

int main() {
    // Test case 1: Regular sorted arrays
    int arr1[] = {1, 3, 5};
    int arr2[] = {2, 4, 6};
    int resultSize;
    int* result = mergeArrays(arr1, 3, arr2, 3, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    free(result);
    
    // Test case 2: One empty array
    int arr4[] = {1, 2, 3};
    result = mergeArrays(NULL, 0, arr4, 3, &resultSize);
    if(result == NULL) printf("Null input handled\\n");
    
    // Test case 3: Arrays with duplicate elements
    int arr5[] = {1, 2, 2};
    int arr6[] = {2, 3, 3};
    result = mergeArrays(arr5, 3, arr6, 3, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    free(result);
    
    // Test case 4: Arrays of different lengths
    int arr7[] = {1, 2, 3, 4};
    int arr8[] = {5, 6};
    result = mergeArrays(arr7, 4, arr8, 2, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    free(result);
    
    // Test case 5: Null arrays
    result = mergeArrays(NULL, 0, NULL, 0, &resultSize);
    if(result == NULL) printf("Null input handled\\n");
    
    return 0;
}
