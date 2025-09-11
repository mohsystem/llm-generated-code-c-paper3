
#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

int shortestSubarray(int* nums, int numsSize, int k) {
    long long* prefixSum = (long long*)malloc((numsSize + 1) * sizeof(long long));
    int* deque = (int*)malloc((numsSize + 1) * sizeof(int));
    int front = 0, rear = 0;
    int result = numsSize + 1;
    
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    
    for (int i = 0; i <= numsSize; i++) {
        while (front < rear && prefixSum[i] <= prefixSum[deque[rear-1]]) {
            rear--;
        }
        while (front < rear && prefixSum[i] >= prefixSum[deque[front]] + k) {
            result = MIN(result, i - deque[front]);
            front++;
        }
        deque[rear++] = i;
    }
    
    free(prefixSum);
    free(deque);
    return result <= numsSize ? result : -1;
}

int main() {
    // Test case 1
    int nums1[] = {1};
    printf("%d\\n", shortestSubarray(nums1, 1, 1));  // Expected: 1
    
    // Test case 2
    int nums2[] = {1,2};
    printf("%d\\n", shortestSubarray(nums2, 2, 4));  // Expected: -1
    
    // Test case 3
    int nums3[] = {2,-1,2};
    printf("%d\\n", shortestSubarray(nums3, 3, 3));  // Expected: 3
    
    // Test case 4
    int nums4[] = {1,1,1,1,1};
    printf("%d\\n", shortestSubarray(nums4, 5, 5));  // Expected: 5
    
    // Test case 5
    int nums5[] = {2,3,1,-1,4};
    printf("%d\\n", shortestSubarray(nums5, 5, 5));  // Expected: 2
    
    return 0;
}
