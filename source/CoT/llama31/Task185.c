#include <stdio.h>
#include <float.h>

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }
    int left = 0, right = m;
    while (left <= right) {
        int i = (left + right) / 2;
        int j = (m + n + 1) / 2 - i;
        double maxLeftX = (i == 0) ? -INFINITY : nums1[i - 1];
        double minRightX = (i == m) ? INFINITY : (i < m ? nums1[i] : INFINITY);
        double maxLeftY = (j == 0) ? -INFINITY : nums2[j - 1];
        double minRightY = (j == n) ? INFINITY : (j < n ? nums2[j] : INFINITY);
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((m + n) % 2 == 0) {
                return (fmax(maxLeftX, maxLeftY) + fmin(minRightX, minRightY)) / 2.0;
            } else {
                return fmax(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            right = i - 1;
        } else {
            left = i + 1;
        }
    }
    return 0.0; // This line should not be reached
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    printf("%f\n", findMedianSortedArrays(nums1, 2, nums2, 1)); // Output: 2.000000

    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    printf("%f\n", findMedianSortedArrays(nums3, 2, nums4, 2)); // Output: 2.500000

    int nums5[] = {1, 2, 3, 4};
    int nums6[] = {5, 6, 7, 8};
    printf("%f\n", findMedianSortedArrays(nums5, 4, nums6, 4)); // Output: 4.500000

    int nums7[] = {1, 3, 5};
    int nums8[] = {2, 4};
    printf("%f\n", findMedianSortedArrays(nums7, 3, nums8, 2)); // Output: 3.000000

    int nums9[] = {0, 0};
    int nums10[] = {0, 0};
    printf("%f\n", findMedianSortedArrays(nums9, 2, nums10, 2)); // Output: 0.000000

    return 0;
}