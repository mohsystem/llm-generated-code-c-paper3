#include <stdio.h>
#include <limits.h>

int maxSumSubsequence(int* nums, int numsSize, int k) {
    int dp[numsSize];
    int deque[numsSize];
    int front = 0, back = 0;
    dp[0] = nums[0];
    deque[back++] = 0;

    for (int i = 1; i < numsSize; i++) {
        while (front < back && deque[front] < i - k) {
            front++;
        }
        dp[i] = nums[i] + (front < back ? dp[deque[front]] : 0);
        while (front < back && dp[i] >= dp[deque[back - 1]]) {
            back--;
        }
        deque[back++] = i;
    }

    int maxSum = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }
    }
    return maxSum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    printf("%d\n", maxSumSubsequence(nums1, 5, 2)); // 37

    int nums2[] = {-1, -2, -3};
    printf("%d\n", maxSumSubsequence(nums2, 3, 1)); // -1

    int nums3[] = {10, -2, -10, -5, 20};
    printf("%d\n", maxSumSubsequence(nums3, 5, 2)); // 23

    int nums4[] = {1, 2, 3, 4, 5};
    printf("%d\n", maxSumSubsequence(nums4, 5, 3)); // 15

    int nums5[] = {-5, -1, -3, -4};
    printf("%d\n", maxSumSubsequence(nums5, 4, 2)); // -1

    return 0;
}