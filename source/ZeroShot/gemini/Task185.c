#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int m = nums1Size;
    int n = nums2Size;
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
                return (double)(maxLeftX > maxLeftY ? maxLeftX : maxLeftY) + (minRightX < minRightY ? minRightX : minRightY) / 2.0;
            } else {
                return (double)(maxLeftX > maxLeftY ? maxLeftX : maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    return -1; // Indicate an error (should ideally throw an exception)
}

int main() {
    int nums11[] = {1, 3};
    int nums12[] = {2};
    printf("%.1f\n", findMedianSortedArrays(nums11, 2, nums12, 1)); // Output: 2.0

    int nums21[] = {1, 2};
    int nums22[] = {3, 4};
    printf("%.1f\n", findMedianSortedArrays(nums21, 2, nums22, 2)); // Output: 2.5

    int nums31[] = {};
    int nums32[] = {1};
    printf("%.1f\n", findMedianSortedArrays(nums31, 0, nums32, 1)); // Output: 1.0

    int nums41[] = {2};
    int nums42[] = {};
    printf("%.1f\n", findMedianSortedArrays(nums41, 1, nums42, 0)); // Output: 2.0

    int nums51[] = {1,2,5};
    int nums52[] = {3,4,6};
    printf("%.1f\n", findMedianSortedArrays(nums51, 3, nums52, 3)); // Output: 3.5


    return 0;
}