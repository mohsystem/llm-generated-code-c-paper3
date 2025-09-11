#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double findMedianSortedArrays(int nums1[], int m, int nums2[], int n) {
    int *merged = (int *)malloc((m + n) * sizeof(int));
    if (merged == NULL) {
        return -1; // Indicate memory allocation failure.
    }

    for (int i = 0; i < m; i++) {
        merged[i] = nums1[i];
    }
    for (int i = 0; i < n; i++) {
        merged[m + i] = nums2[i];
    }

    qsort(merged, m + n, sizeof(int), compare);

    int totalLength = m + n;
    double median;
    if (totalLength % 2 == 0) {
        median = (double)(merged[totalLength / 2 - 1] + merged[totalLength / 2]) / 2;
    } else {
        median = (double)merged[totalLength / 2];
    }
    
    free(merged);
    return median;
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
    
    int nums51[] = {1,2,3,4,5};
    int nums52[] = {1,2,3,4,5};
    printf("%.1f\n", findMedianSortedArrays(nums51, 5, nums52, 5)); // Output: 3.0

    return 0;
}