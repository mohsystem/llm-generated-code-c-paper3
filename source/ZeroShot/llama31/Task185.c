#include <stdio.h>
#include <limits.h>

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }
    int low = 0, high = m;
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((m + n) % 2 == 0) {
                return (double)(max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            } else {
                return (double)max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    return 0; // This line should not be reached
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    printf("%f\n", findMedianSortedArrays(nums1, 2, nums2, 1)); // Output: 2.000000
    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    printf("%f\n", findMedianSortedArrays(nums3, 2, nums4, 2)); // Output: 2.500000
    int nums5[] = {1, 3, 5};
    int nums6[] = {2, 4};
    printf("%f\n", findMedianSortedArrays(nums5, 3, nums6, 2)); // Output: 3.000000
    int nums7[] = {1};
    int nums8[] = {2, 3, 4};
    printf("%f\n", findMedianSortedArrays(nums7, 1, nums8, 3)); // Output: 2.500000
    int nums9[] = {1, 2};
    int nums10[] = {3};
    printf("%f\n", findMedianSortedArrays(nums9, 2, nums10, 1)); // Output: 2.000000
    return 0;
}