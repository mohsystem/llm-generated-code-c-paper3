
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* nums, int* indices, int* counts, int start, int mid, int end) {
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    
    int* merged = (int*)malloc((end - start + 1) * sizeof(int));
    int* mergedIndices = (int*)malloc((end - start + 1) * sizeof(int));
    
    int left = start, right = mid + 1, idx = 0, rightCount = 0;
    
    while(left <= mid && right <= end) {
        if(nums[indices[right]] < nums[indices[left]]) {
            rightCount++;
            mergedIndices[idx] = indices[right];
            merged[idx++] = nums[indices[right++]];
        } else {
            counts[indices[left]] += rightCount;
            mergedIndices[idx] = indices[left];
            merged[idx++] = nums[indices[left++]];
        }
    }
    
    while(left <= mid) {
        counts[indices[left]] += rightCount;
        mergedIndices[idx] = indices[left];
        merged[idx++] = nums[indices[left++]];
    }
    
    while(right <= end) {
        mergedIndices[idx] = indices[right];
        merged[idx++] = nums[indices[right++]];
    }
    
    memcpy(nums + start, merged, (end - start + 1) * sizeof(int));
    memcpy(indices + start, mergedIndices, (end - start + 1) * sizeof(int));
    
    free(merged);
    free(mergedIndices);
}

void mergeSort(int* nums, int* indices, int* counts, int start, int end) {
    if(start >= end) return;
    
    int mid = start + (end - start) / 2;
    mergeSort(nums, indices, counts, start, mid);
    mergeSort(nums, indices, counts, mid + 1, end);
    merge(nums, indices, counts, start, mid, end);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* counts = (int*)calloc(numsSize, sizeof(int));
    int* indices = (int*)malloc(numsSize * sizeof(int));
    
    for(int i = 0; i < numsSize; i++) {
        indices[i] = i;
    }
    
    mergeSort(nums, indices, counts, 0, numsSize - 1);
    
    free(indices);
    return counts;
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
    for(int i = 0; i < 4; i++) printf("%d ", test1[i]);
    result = countSmaller(test1, 4, &returnSize);
    printf("\\nOutput: ");
    for(int i = 0; i < returnSize; i++) printf("%d ", result[i]);
    printf("\\n\\n");
    free(result);
    
    // Test case 2
    printf("Input: ");
    for(int i = 0; i < 1; i++) printf("%d ", test2[i]);
    result = countSmaller(test2, 1, &returnSize);
    printf("\\nOutput: ");
    for(int i = 0; i < returnSize; i++) printf("%d ", result[i]);
    printf("\\n\\n");
    free(result);
    
    // Test case 3
    printf("Input: ");
    for(int i = 0; i < 2; i++) printf("%d ", test3[i]);
    result = countSmaller(test3, 2, &returnSize);
    printf("\\nOutput: ");
    for(int i = 0; i < returnSize; i++) printf("%d ", result[i]);
    printf("\\n\\n");
    free(result);
    
    // Test case 4
    printf("Input: ");
    for(int i = 0; i < 4; i++) printf("%d ", test4[i]);
    result = countSmaller(test4, 4, &returnSize);
    printf("\\nOutput: ");
    for(int i = 0; i < returnSize; i++) printf("%d ", result[i]);
    printf("\\n\\n");
    free(result);
    
    // Test case 5
    printf("Input: ");
    for(int i = 0; i < 4; i++) printf("%d ", test5[i]);
    result = countSmaller(test5, 4, &returnSize);
    printf("\\nOutput: ");
    for(int i = 0; i < returnSize; i++) printf("%d ", result[i]);
    printf("\\n\\n");
    free(result);
    
    return 0;
}
