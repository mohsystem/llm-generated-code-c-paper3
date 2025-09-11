#include <stdio.h>
#include <limits.h>

int shortestSubarray(int* nums, int n, int k) {
    int prefixSum[n + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = prefixSum[j + 1] - prefixSum[i];
            if (sum >= k) {
                ans = (ans < (j - i + 1)) ? ans : (j - i + 1);
            }
        }
    }
    return ans == INT_MAX ? -1 : ans;
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

    int nums4[] = {2, 1, 1, -4, 3, 1, -1, 2};
    int k4 = 5;
    printf("%d\n", shortestSubarray(nums4, 8, k4)); // Output: 4

    int nums5[] = {1, 4, 2, 2, 1, 3, 1, -4, -1, 1};
    int k5 = 7;
    printf("%d\n", shortestSubarray(nums5, 10, k5)); // Output: 3

    return 0;
}