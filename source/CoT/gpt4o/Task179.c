#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(sizeof(int) * (numsSize - k + 1));
    int* deque = (int*)malloc(sizeof(int) * numsSize);
    int front = 0, back = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        if (front < back && deque[front] < i - k + 1) {
            front++;
        }
        
        while (front < back && nums[deque[back - 1]] < nums[i]) {
            back--;
        }
        
        deque[back++] = i;
        
        if (i >= k - 1) {
            result[i - k + 1] = nums[deque[front]];
        }
    }
    
    free(deque);
    *returnSize = numsSize - k + 1;
    return result;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int returnSize;
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int nums2[] = {1};
    int nums3[] = {9, 11};
    int nums4[] = {4, -2};
    int nums5[] = {10, 5, 2, 7, 8, 7};
    
    int* res1 = maxSlidingWindow(nums1, 8, 3, &returnSize);
    printArray(res1, returnSize);
    free(res1);
    
    int* res2 = maxSlidingWindow(nums2, 1, 1, &returnSize);
    printArray(res2, returnSize);
    free(res2);
    
    int* res3 = maxSlidingWindow(nums3, 2, 2, &returnSize);
    printArray(res3, returnSize);
    free(res3);
    
    int* res4 = maxSlidingWindow(nums4, 2, 1, &returnSize);
    printArray(res4, returnSize);
    free(res4);
    
    int* res5 = maxSlidingWindow(nums5, 6, 3, &returnSize);
    printArray(res5, returnSize);
    free(res5);
    
    return 0;
}