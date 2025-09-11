#include <stdio.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    long long prefixSum[numsSize + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int minLen = INT_MAX;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            long long sum = prefixSum[j + 1] - prefixSum[i];
            if (sum >= k) {
                minLen = (minLen < (j - i + 1)) ? minLen : (j - i + 1);
            }
        }
    }

    return minLen == INT_MAX ? -1 : minLen;
}

int main() {
    int nums1[] = {1};
    int k1 = 1;
    printf("Output: %d\n", shortestSubarray(nums1, 1, k1)); // Output: 1

    int nums2[] = {1, 2};
    int k2 = 4;
    printf("Output: %d\n", shortestSubarray(nums2, 2, k2)); // Output: -1

    int nums3[] = {2, -1, 2};
    int k3 = 3;
    printf("Output: %d\n", shortestSubarray(nums3, 3, k3)); // Output: 3

    return 0;
}