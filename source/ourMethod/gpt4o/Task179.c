#include <stdio.h>
#include <stdlib.h>

void maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize, int* result) {
    if (nums == NULL || numsSize <= 0 || k <= 0) {
        *returnSize = 0;
        return;
    }

    int* deque = (int*)malloc(numsSize * sizeof(int));
    int front = 0, back = 0;
    *returnSize = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        if (front < back && deque[front] < i - k + 1) {
            front++;
        }
        
        while (front < back && nums[deque[back - 1]] < nums[i]) {
            back--;
        }
        
        deque[back++] = i;
        
        if (i >= k - 1) {
            result[(*returnSize)++] = nums[deque[front]];
        }
    }
    free(deque);
}

int main() {
    int nums1[] = {1,3,-1,-3,5,3,6,7};
    int nums2[] = {1};
    int nums3[] = {9, 11};
    int nums4[] = {4, -2};
    int nums5[] = {7, 2, 4};
    
    int result1[6];
    int result2[1];
    int result3[1];
    int result4[1];
    int result5[2];
    
    int returnSize1, returnSize2, returnSize3, returnSize4, returnSize5;
    
    maxSlidingWindow(nums1, 8, 3, &returnSize1, result1);
    maxSlidingWindow(nums2, 1, 1, &returnSize2, result2);
    maxSlidingWindow(nums3, 2, 2, &returnSize3, result3);
    maxSlidingWindow(nums4, 2, 2, &returnSize4, result4);
    maxSlidingWindow(nums5, 3, 2, &returnSize5, result5);
    
    for (int i = 0; i < returnSize1; ++i) printf("%d ", result1[i]);
    printf("\n");
    for (int i = 0; i < returnSize2; ++i) printf("%d ", result2[i]);
    printf("\n");
    for (int i = 0; i < returnSize3; ++i) printf("%d ", result3[i]);
    printf("\n");
    for (int i = 0; i < returnSize4; ++i) printf("%d ", result4[i]);
    printf("\n");
    for (int i = 0; i < returnSize5; ++i) printf("%d ", result5[i]);
    printf("\n");

    return 0;
}