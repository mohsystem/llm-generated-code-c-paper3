#include <stdio.h>
#include <limits.h>

int shortestSubarray(int* nums, int n, int k) {
    long long prefixSum[n + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int res = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (prefixSum[j + 1] - prefixSum[i] >= k) {
                res = (res < j - i + 1) ? res : j - i + 1;
            }
        }
    }
    return res == INT_MAX ? -1 : res;
}

int main() {
    int nums1[] = {1};
    int k1 = 1;
    printf("%d\n", shortestSubarray(nums1, 1, k1)); // Output: 1

    int nums2[] = {1, 2};
    int k2 = 4;
    printf("%d\n", shortestSubarray(nums2, 2, k2)); // Output: -1

    int nums3[] = {2, -1, 2};
    int k3 = 3;
    printf("%d\n", shortestSubarray(nums3, 3, k3)); // Output: 3

    int nums4[] = {1, 4, 2, 2, 1, 3, 1};
    int k4 = 7;
    printf("%d\n", shortestSubarray(nums4, 7, k4)); // Output: 2

    int nums5[] = {1, -2, 3, -1, 2};
    int k5 = 3;
    printf("%d\n", shortestSubarray(nums5, 5, k5)); // Output: 3

    return 0;
}