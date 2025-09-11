
#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (nums == NULL || numsSize == 0 || k <= 0) {
        *returnSize = 0;
        return NULL;
    }
    
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    int* deque = (int*)malloc(sizeof(int) * numsSize);  // store indices
    int front = 0, rear = -1;
    int ri = 0;
    
    for (int i = 0; i < numsSize; i++) {
        // remove numbers out of range k
        while (front <= rear && deque[front] < i - k + 1) {
            front++;
        }
        
        // remove smaller numbers in k range as they are not needed
        while (front <= rear && nums[deque[rear]] < nums[i]) {
            rear--;
        }
        
        deque[++rear] = i;
        
        if (i >= k - 1) {
            result[ri++] = nums[deque[front]];
        }
    }
    
    free(deque);
    return result;
}

void printArray(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\\n");
}

int main() {
    // Test case 1
    int nums1[] = {1,3,-1,-3,5,3,6,7};
    int k1 = 3;
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, 8, k1, &returnSize1);
    printf("Test case 1: ");
    printArray(result1, returnSize1);
    free(result1);
    
    // Test case 2
    int nums2[] = {1};
    int k2 = 1;
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, 1, k2, &returnSize2);
    printf("Test case 2: ");
    printArray(result2, returnSize2);
    free(result2);
    
    // Test case 3
    int nums3[] = {1,-1};
    int k3 = 1;
    int returnSize3;
    int* result3 = maxSlidingWindow(nums3, 2, k3, &returnSize3);
    printf("Test case 3: ");
    printArray(result3, returnSize3);
    free(result3);
    
    // Test case 4
    int nums4[] = {1,2,3,4,5};
    int k4 = 3;
    int returnSize4;
    int* result4 = maxSlidingWindow(nums4, 5, k4, &returnSize4);
    printf("Test case 4: ");
    printArray(result4, returnSize4);
    free(result4);
    
    // Test case 5
    int nums5[] = {1,2,3,4,5,4,3,2,1};
    int k5 = 4;
    int returnSize5;
    int* result5 = maxSlidingWindow(nums5, 9, k5, &returnSize5);
    printf("Test case 5: ");
    printArray(result5, returnSize5);
    free(result5);
    
    return 0;
}
