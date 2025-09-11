#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Descending order
}

int findKthLargest(int nums[], int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    return nums[k - 1];
}

int main() {
    int nums1[] = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    printf("%d\n", findKthLargest(nums1, 6, k1)); // Output: 5

    int nums2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    printf("%d\n", findKthLargest(nums2, 9, k2)); // Output: 4

    int nums3[] = {1};
    int k3 = 1;
    printf("%d\n", findKthLargest(nums3, 1, k3)); // Output: 1

    int nums4[] = {1, 2};
    int k4 = 2;
    printf("%d\n", findKthLargest(nums4, 2, k4)); // Output: 1


    int nums5[] = {5, 4, 3, 2, 1};
    int k5 = 3;
    printf("%d\n", findKthLargest(nums5, 5, k5)); // Output: 3

    return 0;
}