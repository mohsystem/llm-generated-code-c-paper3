#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    long* prefixSum = (long*)malloc((numsSize + 1) * sizeof(long));
    for (int i = 0; i < numsSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    
    int* deque = (int*)malloc((numsSize + 1) * sizeof(int));
    int front = 0, back = 0;
    int minLength = numsSize + 1;
    
    for (int i = 0; i <= numsSize; ++i) {
        while (front < back && prefixSum[i] - prefixSum[deque[front]] >= k) {
            minLength = i - deque[front];
            front++;
        }
        while (front < back && prefixSum[i] <= prefixSum[deque[back - 1]]) {
            back--;
        }
        deque[back++] = i;
    }
    
    free(prefixSum);
    free(deque);
    return minLength <= numsSize ? minLength : -1;
}

int main() {
    int nums1[] = {1};
    printf("%d\n", shortestSubarray(nums1, 1, 1)); // Output: 1
    
    int nums2[] = {1, 2};
    printf("%d\n", shortestSubarray(nums2, 2, 4)); // Output: -1
    
    int nums3[] = {2, -1, 2};
    printf("%d\n", shortestSubarray(nums3, 3, 3)); // Output: 3
    
    int nums4[] = {1, 2, 3, 4, 5};
    printf("%d\n", shortestSubarray(nums4, 5, 11)); // Output: 3
    
    int nums5[] = {-1, -2, -3, 4, 5};
    printf("%d\n", shortestSubarray(nums5, 5, 6)); // Output: 2
    
    return 0;
}