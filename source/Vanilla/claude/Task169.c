
#include <stdio.h>
#include <stdlib.h>

void merge(int* nums, int* indices, int start, int end, int mid, int* result) {
    int leftLen = mid - start + 1;
    int rightLen = end - mid;
    
    int* leftIndices = (int*)malloc(leftLen * sizeof(int));
    int* rightIndices = (int*)malloc(rightLen * sizeof(int));
    
    for(int i = 0; i < leftLen; i++) {
        leftIndices[i] = indices[start + i];
    }
    for(int i = 0; i < rightLen; i++) {
        rightIndices[i] = indices[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = start;
    int rightCount = 0;
    
    while(i < leftLen && j < rightLen) {
        if(nums[leftIndices[i]] <= nums[rightIndices[j]]) {
            result[leftIndices[i]] += rightCount;
            indices[k++] = leftIndices[i++];
        } else {
            rightCount++;
            indices[k++] = rightIndices[j++];
        }
    }
    
    while(i < leftLen) {
        result[leftIndices[i]] += rightCount;
        indices[k++] = leftIndices[i++];
    }
    
    while(j < rightLen) {
        indices[k++] = rightIndices[j++];
    }
    
    free(leftIndices);
    free(rightIndices);
}

void mergeSort(int* nums, int* indices, int start, int end, int* result) {
    if(start >= end) return;
    
    int mid = start + (end - start)/2;
    mergeSort(nums, indices, start, mid, result);
    mergeSort(nums, indices, mid+1, end, result);
    
    merge(nums, indices, start, end, mid, result);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* result = (int*)calloc(numsSize, sizeof(int));
    int* indices = (int*)malloc(numsSize * sizeof(int));
    
    for(int i = 0; i < numsSize; i++) {
        indices[i] = i;
    }
    
    mergeSort(nums, indices, 0, numsSize-1, result);
    
    free(indices);
    return result;
}

int main() {
    // Test case 1
    int nums1[] = {5,2,6,1};
    int returnSize1;
    int* result1 = countSmaller(nums1, 4, &returnSize1);
    for(int i = 0; i < returnSize1; i++) printf("%d ", result1[i]);
    printf("\\n");
    free(result1);
    
    // Test case 2
    int nums2[] = {-1};
    int returnSize2;
    int* result2 = countSmaller(nums2, 1, &returnSize2);
    for(int i = 0; i < returnSize2; i++) printf("%d ", result2[i]);
    printf("\\n");
    free(result2);
    
    // Test case 3
    int nums3[] = {-1,-1};
    int returnSize3;
    int* result3 = countSmaller(nums3, 2, &returnSize3);
    for(int i = 0; i < returnSize3; i++) printf("%d ", result3[i]);
    printf("\\n");
    free(result3);
    
    // Test case 4
    int nums4[] = {1,2,3,4};
    int returnSize4;
    int* result4 = countSmaller(nums4, 4, &returnSize4);
    for(int i = 0; i < returnSize4; i++) printf("%d ", result4[i]);
    printf("\\n");
    free(result4);
    
    // Test case 5
    int nums5[] = {4,3,2,1};
    int returnSize5;
    int* result5 = countSmaller(nums5, 4, &returnSize5);
    for(int i = 0; i < returnSize5; i++) printf("%d ", result5[i]);
    printf("\\n");
    free(result5);
    
    return 0;
}
