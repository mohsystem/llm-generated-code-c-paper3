
#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (nums == NULL || numsSize == 0 || k <= 0) {
        *returnSize = 0;
        return NULL;
    }
    
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    int* deque = (int*)malloc(sizeof(int) * numsSize);
    int front = 0, rear = -1;
    
    for (int i = 0; i < k; i++) {
        while (front <= rear && nums[i] >= nums[deque[rear]]) {
            rear--;
        }
        deque[++rear] = i;
    }
    
    for (int i = k; i < numsSize; i++) {
        result[i-k] = nums[deque[front]];
        
        while (front <= rear && deque[front] <= i-k) {
            front++;
        }
        
        while (front <= rear && nums[i] >= nums[deque[rear]]) {
            rear--;
        }
        
        deque[++rear] = i;
    }
    
    result[numsSize-k] = nums[deque[front]];
    
    free(deque);
    return result;
}

int main() {
    // Test case 1
    int nums1[] = {1,3,-1,-3,5,3,6,7};
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, 8, 3, &returnSize1);
    for (int i = 0; i < returnSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\\n");
    free(result1);
    
    // Test case 2
    int nums2[] = {1};
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, 1, 1, &returnSize2);
    for (int i = 0; i < returnSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\\n");
    free(result2);
    
    // Test case 3
    int nums3[] = {1,2,3,4,5};
    int returnSize3;
    int* result3 = maxSlidingWindow(nums3, 5, 2, &returnSize3);
    for (int i = 0; i < returnSize3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\\n");
    free(result3);
    
    // Test case 4
    int nums4[] = {-1,-2,-3,-4};
    int returnSize4;
    int* result4 = maxSlidingWindow(nums4, 4, 3, &returnSize4);
    for (int i = 0; i < returnSize4; i++) {
        printf("%d ", result4[i]);
    }
    printf("\\n");
    free(result4);
    
    // Test case 5
    int nums5[] = {1,1,1,1};
    int returnSize5;
    int* result5 = maxSlidingWindow(nums5, 4, 2, &returnSize5);
    for (int i = 0; i < returnSize5; i++) {
        printf("%d ", result5[i]);
    }
    printf("\\n");
    free(result5);
    
    return 0;
}
