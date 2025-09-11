
#include <stdio.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0) {
        return -1;
    }
    
    int minLen = INT_MAX;
    
    for (int start = 0; start < numsSize; start++) {
        long long sum = 0;
        for (int end = start; end < numsSize; end++) {
            sum += nums[end];
            if (sum >= k) {
                int len = end - start + 1;
                minLen = (len < minLen) ? len : minLen;
                break;
            }
        }
    }
    
    return minLen == INT_MAX ? -1 : minLen;
}

int main() {
    // Test case 1
    int nums1[] = {1};
    printf("%d\\n", shortestSubarray(nums1, 1, 1));  // Expected: 1
    
    // Test case 2
    int nums2[] = {1, 2};
    printf("%d\\n", shortestSubarray(nums2, 2, 4));  // Expected: -1
    
    // Test case 3
    int nums3[] = {2, -1, 2};
    printf("%d\\n", shortestSubarray(nums3, 3, 3));  // Expected: 3
    
    // Test case 4
    int nums4[] = {1, 2, 3, 4, 5};
    printf("%d\\n", shortestSubarray(nums4, 5, 9));  // Expected: 2
    
    // Test case 5
    int nums5[] = {-1, 2, 3};
    printf("%d\\n", shortestSubarray(nums5, 3, 5));  // Expected: 2
    
    return 0;
}
