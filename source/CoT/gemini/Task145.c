#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int nums[], int n) {
    int maxSoFar = INT_MIN;
    int currentMax = 0;

    for (int i = 0; i < n; i++) {
        currentMax += nums[i];
        if (currentMax > maxSoFar) {
            maxSoFar = currentMax;
        }
        if (currentMax < 0) {
            currentMax = 0;
        }
    }

    return maxSoFar;
}

int main() {
    int nums1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("%d\n", maxSubArraySum(nums1, n1)); // Output: 6

    int nums2[] = {-1};
    int n2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("%d\n", maxSubArraySum(nums2, n2)); // Output: -1

    int nums3[] = {1};
    int n3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("%d\n", maxSubArraySum(nums3, n3)); // Output: 1

    int nums4[] = {5, 4, -1, 7, 8};
    int n4 = sizeof(nums4) / sizeof(nums4[0]);
    printf("%d\n", maxSubArraySum(nums4, n4)); // Output: 23

    int nums5[] = {-2, -3, -1, -5};
    int n5 = sizeof(nums5) / sizeof(nums5[0]);
    printf("%d\n", maxSubArraySum(nums5, n5)); // Output: -1

    return 0;
}