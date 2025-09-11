#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int* merged = (int*)malloc((nums1Size + nums2Size) * sizeof(int));
    if (merged == NULL) {
        return 0.0; // Handle memory allocation failure
    }

    for (int i = 0; i < nums1Size; i++) {
        merged[i] = nums1[i];
    }
    for (int i = 0; i < nums2Size; i++) {
        merged[nums1Size + i] = nums2[i];
    }

    qsort(merged, nums1Size + nums2Size, sizeof(int), compare);

    int totalLength = nums1Size + nums2Size;
    if (totalLength % 2 == 0) {
        double median = (double)(merged[totalLength / 2 - 1] + merged[totalLength / 2]) / 2;
        free(merged);
        return median;
    } else {
        double median = (double)merged[totalLength / 2];
        free(merged);
        return median;
    }
}

int main() {
    int nums11[] = {1, 3};
    int nums21[] = {2};
    printf("%f\n", findMedianSortedArrays(nums11, 2, nums21, 1)); // Output: 2.0

    int nums12[] = {1, 2};
    int nums22[] = {3, 4};
    printf("%f\n", findMedianSortedArrays(nums12, 2, nums22, 2)); // Output: 2.5

    int nums13[] = {};
    int nums23[] = {1};
    printf("%f\n", findMedianSortedArrays(nums13, 0, nums23, 1)); // Output: 1.0

    int nums14[] = {2};
    int nums24[] = {};
    printf("%f\n", findMedianSortedArrays(nums14, 1, nums24, 0)); // Output: 2.0

    int nums15[] = {1, 2, 5};
    int nums25[] = {3, 4, 6};
    printf("%f\n", findMedianSortedArrays(nums15, 3, nums25, 3)); // Output: 3.5


    return 0;
}