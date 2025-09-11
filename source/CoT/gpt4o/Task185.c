#include <stdio.h>

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }
    int imin = 0, imax = m, halfLen = (m + n + 1) / 2;
    while (imin <= imax) {
        int i = (imin + imax) / 2;
        int j = halfLen - i;
        if (i < m && nums2[j-1] > nums1[i]) {
            imin = i + 1;
        } else if (i > 0 && nums1[i-1] > nums2[j]) {
            imax = i - 1;
        } else {
            int maxOfLeft;
            if (i == 0) { maxOfLeft = nums2[j-1]; }
            else if (j == 0) { maxOfLeft = nums1[i-1]; }
            else { maxOfLeft = (nums1[i-1] > nums2[j-1]) ? nums1[i-1] : nums2[j-1]; }
            if ((m + n) % 2 == 1) { return maxOfLeft; }

            int minOfRight;
            if (i == m) { minOfRight = nums2[j]; }
            else if (j == n) { minOfRight = nums1[i]; }
            else { minOfRight = (nums2[j] < nums1[i]) ? nums2[j] : nums1[i]; }

            return (maxOfLeft + minOfRight) / 2.0;
        }
    }
    return 0.0;
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    printf("%lf\n", findMedianSortedArrays(nums1, 2, nums2, 1)); // 2.00000

    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    printf("%lf\n", findMedianSortedArrays(nums3, 2, nums4, 2)); // 2.50000

    int nums5[] = {0, 0};
    int nums6[] = {0, 0};
    printf("%lf\n", findMedianSortedArrays(nums5, 2, nums6, 2)); // 0.00000

    int nums7[] = {};
    int nums8[] = {1};
    printf("%lf\n", findMedianSortedArrays(nums7, 0, nums8, 1)); // 1.00000

    int nums9[] = {2};
    int nums10[] = {1, 3};
    printf("%lf\n", findMedianSortedArrays(nums9, 1, nums10, 2)); // 2.00000

    return 0;
}