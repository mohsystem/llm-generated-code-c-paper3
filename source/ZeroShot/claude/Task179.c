
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
    int front = 0, rear = 0;
    
    for (int i = 0; i < numsSize; i++) {
        // Remove elements outside current window
        while (front < rear && deque[front] < i - k + 1) {
            front++;
        }
        
        // Remove elements smaller than current element
        while (front < rear && nums[deque[rear - 1]] < nums[i]) {
            rear--;
        }
        
        deque[rear++] = i;
        
        // Add to result if we have a complete window
        if (i >= k - 1) {
            result[i - k + 1] = nums[deque[front]];
        }
    }
    
    free(deque);
    return result;
}

void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\\n");
}

int main() {
    // Test case 1
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, 8, 3, &returnSize1);
    printArray(result1, returnSize1);
    free(result1);
    
    // Test case 2
    int nums2[] = {1};
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, 1, 1, &returnSize2);
    printArray(result2, returnSize2);
    free(result2);
    
    // Test case 3
    int nums3[] = {1, 2, 3, 4, 5};
    int returnSize3;
    int* result3 = maxSlidingWindow(nums3, 5, 2, &returnSize3);
    printArray(result3, returnSize3);
    free(result3);
    
    // Test case 4
    int nums4[] = {1, -1};
    int returnSize4;
    int* result4 = maxSlidingWindow(nums4, 2, 1, &returnSize4);
    printArray(result4, returnSize4);
    free(result4);
    
    // Test case 5
    int nums5[] = {7, 2, 4};
    int returnSize5;
    int* result5 = maxSlidingWindow(nums5, 3, 2, &returnSize5);
    printArray(result5, returnSize5);
    free(result5);
    
    return 0;
}
