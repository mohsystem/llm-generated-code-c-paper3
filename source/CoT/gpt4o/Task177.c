#include <stdio.h>
#include <stdlib.h>

int maxSumSubsequence(int* nums, int numsSize, int k) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int front = 0, back = 0;
    int maxSum = nums[0];

    dp[0] = nums[0];
    deque[back++] = 0;

    for (int i = 1; i < numsSize; i++) {
        if (front < back && deque[front] < i - k) {
            front++;
        }
        dp[i] = nums[i] + (front < back ? dp[deque[front]] : 0);
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }
        while (front < back && dp[deque[back - 1]] <= dp[i]) {
            back--;
        }
        deque[back++] = i;
    }

    free(dp);
    free(deque);
    return maxSum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    printf("%d\n", maxSumSubsequence(nums1, 5, 2));  // Output: 37

    int nums2[] = {-1, -2, -3};
    printf("%d\n", maxSumSubsequence(nums2, 3, 1));  // Output: -1

    int nums3[] = {10, -2, -10, -5, 20};
    printf("%d\n", maxSumSubsequence(nums3, 5, 2));  // Output: 23

    int nums4[] = {5, 3, 2, -1, 4};
    printf("%d\n", maxSumSubsequence(nums4, 5, 3));  // Output: 13

    int nums5[] = {1, -1, -1, 1, 1};
    printf("%d\n", maxSumSubsequence(nums5, 5, 1));  // Output: 2

    return 0;
}