#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int findKthLargest(int* nums, int size, int k) {
    qsort(nums, size, sizeof(int), compare);
    return nums[size - k];
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

    int nums4[] = {7, 10, 4, 3, 20, 15};
    int k4 = 3;
    printf("%d\n", findKthLargest(nums4, 6, k4)); // Output: 10

    int nums5[] = {7, 10, 4, 20, 15};
    int k5 = 4;
    printf("%d\n", findKthLargest(nums5, 5, k5)); // Output: 7

    return 0;
}