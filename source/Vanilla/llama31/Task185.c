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
                return ((double) (max(maxLeftX, maxLeftY) + min(minRightX, minRightY))) / 2;
            } else {
                return (double) max(maxLeftX, maxLeftY);
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
    int nums1[][4] = {{1, 3}, {1, 2}, {900}, {}};
    int nums2[][4] = {{2}, {3, 4}, {10, 13, 14}, {1}};
    int lengths1[] = {2, 2, 1, 0};
    int lengths2[] = {1, 2, 3, 1};
    for (int i = 0; i < 4; i++) {
        printf("The median is : %f\n", findMedianSortedArrays(nums1[i], lengths1[i], nums2[i], lengths2[i]));
    }
    return 0;
}