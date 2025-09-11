
#include <stdio.h>
#include <stdlib.h>

int countRangeSums(int* nums, int numsSize, int lower, int upper) {
    long long* prefixSum = (long long*)malloc((numsSize + 1) * sizeof(long long));
    prefixSum[0] = 0;
    
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            long long sum = prefixSum[j + 1] - prefixSum[i];
            if (sum >= lower && sum <= upper) {
                count++;
            }
        }
    }
    
    free(prefixSum);
    return count;
}

int main() {
    // Test case 1
    int nums1[] = {-2,5,-1};
    printf("%d\\n", countRangeSums(nums1, 3, -2, 2));  // Expected: 3
    
    // Test case 2
    int nums2[] = {0};
    printf("%d\\n", countRangeSums(nums2, 1, 0, 0));  // Expected: 1
    
    // Test case 3
    int nums3[] = {1,2,3};
    printf("%d\\n", countRangeSums(nums3, 3, 2, 5));  // Expected: 4
    
    // Test case 4
    int nums4[] = {-1,-1};
    printf("%d\\n", countRangeSums(nums4, 2, -2, 0));  // Expected: 3
    
    // Test case 5
    int nums5[] = {1,-1,1,-1};
    printf("%d\\n", countRangeSums(nums5, 4, -1, 1));  // Expected: 8
    
    return 0;
}
