
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSubsequenceSum(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k < 1) {
        return 0;
    }
    
    int* dp = (int*)malloc(numsSize * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    dp[0] = nums[0];
    int maxSum = dp[0];
    
    for (int i = 1; i < numsSize; i++) {
        dp[i] = nums[i];
        for (int j = max(0, i-k); j < i; j++) {
            dp[i] = max(dp[i], dp[j] + nums[i]);
        }
        maxSum = max(maxSum, dp[i]);
    }
    
    free(dp);
    return maxSum;
}

int main() {
    // Test case 1
    int nums1[] = {10,2,-10,5,20};
    printf("%d\\n", maxSubsequenceSum(nums1, 5, 2));  // Expected: 37
    
    // Test case 2
    int nums2[] = {-1,-2,-3};
    printf("%d\\n", maxSubsequenceSum(nums2, 3, 1));  // Expected: -1
    
    // Test case 3
    int nums3[] = {10,-2,-10,-5,20};
    printf("%d\\n", maxSubsequenceSum(nums3, 5, 2));  // Expected: 23
    
    // Test case 4
    int nums4[] = {1,2,3,4,5};
    printf("%d\\n", maxSubsequenceSum(nums4, 5, 3));  // Expected: 15
    
    // Test case 5
    int nums5[] = {-5,-4,-3,-2,-1};
    printf("%d\\n", maxSubsequenceSum(nums5, 5, 2));  // Expected: -1
    
    return 0;
}
