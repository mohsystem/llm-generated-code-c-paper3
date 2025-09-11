
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int constrainedSubsetSum(int* nums, int numsSize, int k) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    int maxSum = nums[0];
    
    // Initialize dp array
    for (int i = 0; i < numsSize; i++) {
        dp[i] = nums[i];
    }
    
    // For each position, look back up to k positions
    for (int i = 1; i < numsSize; i++) {
        int maxPrev = 0;
        for (int j = max(0, i-k); j < i; j++) {
            maxPrev = max(maxPrev, dp[j]);
        }
        if (maxPrev > 0) {
            dp[i] += maxPrev;
        }
        maxSum = max(maxSum, dp[i]);
    }
    
    free(dp);
    return maxSum;
}

int main() {
    // Test case 1
    int nums1[] = {10,2,-10,5,20};
    printf("%d\\n", constrainedSubsetSum(nums1, 5, 2));  // Expected: 37
    
    // Test case 2
    int nums2[] = {-1,-2,-3};
    printf("%d\\n", constrainedSubsetSum(nums2, 3, 1));  // Expected: -1
    
    // Test case 3
    int nums3[] = {10,-2,-10,-5,20};
    printf("%d\\n", constrainedSubsetSum(nums3, 5, 2));  // Expected: 23
    
    // Test case 4
    int nums4[] = {1,2,3,4,5};
    printf("%d\\n", constrainedSubsetSum(nums4, 5, 1));  // Expected: 15
    
    // Test case 5
    int nums5[] = {-1,-2,-3,-4,-5};
    printf("%d\\n", constrainedSubsetSum(nums5, 5, 3));  // Expected: -1
    
    return 0;
}
