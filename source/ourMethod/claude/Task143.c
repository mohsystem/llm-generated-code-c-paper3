
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temp arrays
    int* leftArray = (int*)malloc(n1 * sizeof(int));
    int* rightArray = (int*)malloc(n2 * sizeof(int));
    
    if (leftArray == NULL || rightArray == NULL) {
        if (leftArray) free(leftArray);
        if (rightArray) free(rightArray);
        return;  // Handle memory allocation failure
    }
    
    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = arr[mid + 1 + j];
    
    // Merge temp arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
    
    // Free allocated memory
    free(leftArray);
    free(rightArray);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // Prevents overflow
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

int* sortArray(const int arr[], int size, int* resultSize) {
    if (arr == NULL || size <= 0) {
        *resultSize = 0;
        return NULL;
    }
    
    // Create copy of input array
    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        *resultSize = 0;
        return NULL;
    }
    
    memcpy(result, arr, size * sizeof(int));
    *resultSize = size;
    
    mergeSort(result, 0, size - 1);
    return result;
}

void printArray(const int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]");
}

int main() {
    // Test cases
    int test1[] = {64, 34, 25, 12, 22, 11, 90};
    int test2[] = {1};
    int test3[] = {5, 5, 5, 5, 5};
    int test4[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    int* testCases[] = {test1, test2, test3, test4};
    int sizes[] = {7, 1, 5, 9};
    
    for (int i = 0; i < 4; i++) {
        printf("Test case %d - Original: ", i + 1);
        printArray(testCases[i], sizes[i]);
        
        int resultSize;
        int* sorted = sortArray(testCases[i], sizes[i], &resultSize);
        
        if (sorted != NULL) {
            printf("\\nSorted: ");
            printArray(sorted, resultSize);
            printf("\\n\\n");
            free(sorted);
        } else {
            printf("\\nError: Sorting failed\\n\\n");
        }
    }
    
    return 0;
}
