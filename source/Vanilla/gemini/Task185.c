#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int* merged = (int*)malloc((nums1Size + nums2Size) * sizeof(int));
    int i = 0, j = 0, k = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] <= nums2[j]) {
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
    int len = nums1Size + nums2Size;
    if (len % 2 == 0) {
        double result = (double)(merged[len / 2 - 1] + merged[len / 2]) / 2;
        free(merged);
        return result;
    } else {
        double result = (double)merged[len / 2];
        free(merged);
        return result;
    }
}

int main() {
    int nums11[] = {1, 3};
    int nums12[] = {2};
    printf("%f\n", findMedianSortedArrays(nums11, 2, nums12, 1)); // 2.0

    int nums21[] = {1, 2};
    int nums22[] = {3, 4};
    printf("%f\n", findMedianSortedArrays(nums21, 2, nums22, 2)); // 2.5

    int nums31[] = {};
    int nums32[] = {1};
    printf("%f\n", findMedianSortedArrays(nums31, 0, nums32, 1)); // 1.0

    int nums41[] = {2};
    int nums42[] = {};
    printf("%f\n", findMedianSortedArrays(nums41, 1, nums42, 0)); // 2.0

    int nums51[] = {1,2,4,5,7};
    int nums52[] = {3,6,8,9};
    printf("%f\n", findMedianSortedArrays(nums51, 5, nums52, 4)); // 5.0

    return 0;
}