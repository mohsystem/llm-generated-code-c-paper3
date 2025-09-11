#include <stdio.h>
#include <stdlib.h>

int maxSubsequenceSum(int* nums, int numsSize, int k) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int front = 0, back = 0, result = nums[0];
    
    dp[0] = nums[0];
    deque[back++] = 0;
    
    for (int i = 1; i < numsSize; i++) {
        if (front < back && deque[front] < i - k) {
            front++;
        }
        dp[i] = nums[i] + (front < back ? dp[deque[front]] : 0);
        while (front < back && dp[deque[back - 1]] <= dp[i]) {
            back--;
        }
        deque[back++] = i;
        if (dp[i] > result) {
            result = dp[i];
        }
    }
    
    free(dp);
    free(deque);
    return result;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    int nums2[] = {-1, -2, -3};
    int nums3[] = {10, -2, -10, -5, 20};
    int nums4[] = {1, 2, 3, 4, 5};
    int nums5[] = {5, -1, 5, -2, 5};
    
    printf("%d\n", maxSubsequenceSum(nums1, 5, 2)); // 37
    printf("%d\n", maxSubsequenceSum(nums2, 3, 1)); // -1
    printf("%d\n", maxSubsequenceSum(nums3, 5, 2)); // 23
    printf("%d\n", maxSubsequenceSum(nums4, 5, 2)); // 15
    printf("%d\n", maxSubsequenceSum(nums5, 5, 1)); // 12
    
    return 0;
}