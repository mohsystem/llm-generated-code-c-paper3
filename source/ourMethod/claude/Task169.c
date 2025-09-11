
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_sorted(int* sorted, int* size, int value, int pos) {
    for (int i = *size; i > pos; i--) {
        sorted[i] = sorted[i-1];
    }
    sorted[pos] = value;
    (*size)++;
}

int find_insert_position(const int* sorted, int size, int target) {
    int left = 0;
    int right = size;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (sorted[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    if (nums == NULL || numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int* result = (int*)calloc(numsSize, sizeof(int));
    if (!result) return NULL;
    
    int* sorted = (int*)malloc(numsSize * sizeof(int));
    if (!sorted) {
        free(result);
        return NULL;
    }
    
    int sortedSize = 0;
    
    for (int i = numsSize - 1; i >= 0; i--) {
        int pos = find_insert_position(sorted, sortedSize, nums[i]);
        result[i] = pos;
        insert_sorted(sorted, &sortedSize, nums[i], pos);
    }
    
    free(sorted);
    *returnSize = numsSize;
    return result;
}

void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\\n");
}

int main() {
    // Test cases
    int test1[] = {5, 2, 6, 1};
    int test2[] = {-1};
    int test3[] = {-1, -1};
    int test4[] = {1, 2, 3, 4};
    int test5[] = {4, 3, 2, 1};
    
    int returnSize;
    int* result;
    
    // Test case 1
    printf("Input: ");
    printArray(test1, 4);
    result = countSmaller(test1, 4, &returnSize);
    printf("Output: ");
    printArray(result, returnSize);
    free(result);
    printf("\\n");
    
    // Test case 2
    printf("Input: ");
    printArray(test2, 1);
    result = countSmaller(test2, 1, &returnSize);
    printf("Output: ");
    printArray(result, returnSize);
    free(result);
    printf("\\n");
    
    // Test case 3
    printf("Input: ");
    printArray(test3, 2);
    result = countSmaller(test3, 2, &returnSize);
    printf("Output: ");
    printArray(result, returnSize);
    free(result);
    printf("\\n");
    
    // Test case 4
    printf("Input: ");
    printArray(test4, 4);
    result = countSmaller(test4, 4, &returnSize);
    printf("Output: ");
    printArray(result, returnSize);
    free(result);
    printf("\\n");
    
    // Test case 5
    printf("Input: ");
    printArray(test5, 4);
    result = countSmaller(test5, 4, &returnSize);
    printf("Output: ");
    printArray(result, returnSize);
    free(result);
    
    return 0;
}
