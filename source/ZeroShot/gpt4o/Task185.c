#include <stdio.h>
#include <limits.h>

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }

    int x = m;
    int y = n;
    int low = 0, high = x;

    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;

        int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minX = (partitionX == x) ? INT_MAX : nums1[partitionX];

        int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minY = (partitionY == y) ? INT_MAX : nums2[partitionY];

        if (maxX <= minY && maxY <= minX) {
            if ((x + y) % 2 == 0) {
                return ((double)((maxX > maxY ? maxX : maxY) + (minX < minY ? minX : minY))) / 2;
            } else {
                return (double)(maxX > maxY ? maxX : maxY);
            }
        } else if (maxX > minY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }

    return -1; // If input arrays are not sorted
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    printf("%lf\n", findMedianSortedArrays(nums1, 2, nums2, 1)); // 2.0

    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    printf("%lf\n", findMedianSortedArrays(nums3, 2, nums4, 2)); // 2.5

    int nums5[] = {0, 0};
    int nums6[] = {0, 0};
    printf("%lf\n", findMedianSortedArrays(nums5, 2, nums6, 2)); // 0.0

    int nums7[] = {};
    int nums8[] = {1};
    printf("%lf\n", findMedianSortedArrays(nums7, 0, nums8, 1)); // 1.0

    int nums9[] = {2};
    int nums10[] = {1, 3, 4};
    printf("%lf\n", findMedianSortedArrays(nums9, 1, nums10, 3)); // 2.5

    return 0;
}