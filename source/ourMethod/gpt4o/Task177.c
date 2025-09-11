#include <stdio.h>
#include <stdlib.h>

int maxSubsequenceSum(int* nums, int numsSize, int k) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    dp[0] = nums[0];
    int maxSum = nums[0];
    int* dequeIndices = (int*)malloc(numsSize * sizeof(int));
    int front = 0, back = 0;
    dequeIndices[back++] = 0;

    for (int i = 1; i < numsSize; i++) {
        while (front < back && dequeIndices[front] < i - k) {
            front++;
        }
        dp[i] = nums[i] + (front < back ? (dp[dequeIndices[front]] > 0 ? dp[dequeIndices[front]] : 0) : 0);
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }
        
        while (front < back && dp[dequeIndices[back - 1]] <= dp[i]) {
            back--;
        }
        dequeIndices[back++] = i;
    }
    
    free(dp);
    free(dequeIndices);
    return maxSum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    printf("%d\n", maxSubsequenceSum(nums1, 5, 2)); // 37

    int nums2[] = {-1, -2, -3};
    printf("%d\n", maxSubsequenceSum(nums2, 3, 1)); // -1

    int nums3[] = {10, -2, -10, -5, 20};
    printf("%d\n", maxSubsequenceSum(nums3, 5, 2)); // 23

    int nums4[] = {1, 2, 3, 4, 5};
    printf("%d\n", maxSubsequenceSum(nums4, 5, 3)); // 15

    int nums5[] = {5, -1, 2, 3, 4};
    printf("%d\n", maxSubsequenceSum(nums5, 5, 2)); // 12

    return 0;
}