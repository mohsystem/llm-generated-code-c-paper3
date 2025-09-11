#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int* merged = malloc((nums1Size + nums2Size) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] < nums2[j]) {
            merged[k++] = nums1[i++];
        } else {
            merged[k++] = nums2[j++];
        }
    }

    while (i < nums1Size) {
        merged[k++] = nums1[i++];
    }

    while (j < nums2Size) {
        merged[k++] = nums2[j++];
    }

    int n = nums1Size + nums2Size;
    double median;
    if (n % 2 == 0) {
        median = (merged[n / 2 - 1] + merged[n / 2]) / 2.0;
    } else {
        median = merged[n / 2];
    }

    free(merged);
    return median;
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    printf("%f\n", findMedianSortedArrays(nums1, 2, nums2, 1)); // 2.0

    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    printf("%f\n", findMedianSortedArrays(nums3, 2, nums4, 2)); // 2.5

    return 0;
}