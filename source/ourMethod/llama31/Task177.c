#include <stdio.h>
#include <stdlib.h>

int constrainedSubsetSum(int* nums, int numsSize, int k) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    dp[0] = nums[0];
    int max_sum = nums[0];

    for (int i = 1; i < numsSize; i++) {
        int sum = nums[i];
        for (int j = 1; j <= k && i - j >= 0; j++) {
            sum = (sum > dp[i - j] + nums[i]) ? sum : dp[i - j] + nums[i];
        }
        dp[i] = sum;
        max_sum = (max_sum > sum) ? max_sum : sum;
    }

    free(dp);
    return max_sum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    int k1 = 2;
    printf("%d\n", constrainedSubsetSum(nums1, 5, k1)); // Output: 37

    int nums2[] = {-1, -2, -3};
    int k2 = 1;
    printf("%d\n", constrainedSubsetSum(nums2, 3, k2)); // Output: -1

    int nums3[] = {10, -2, -10, -5, 20};
    int k3 = 2;
    printf("%d\n", constrainedSubsetSum(nums3, 5, k3)); // Output: 23

    return 0;
}