#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int findKthLargest(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    return nums[k - 1];
}

int main() {
    int nums1[] = {3, 2, 1, 5, 6, 4};
    printf("%d\n", findKthLargest(nums1, 6, 2)); // 5

    int nums2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    printf("%d\n", findKthLargest(nums2, 9, 4)); // 4

    int nums3[] = {1, 2, 3, 4, 5, 6};
    printf("%d\n", findKthLargest(nums3, 6, 1)); // 6

    int nums4[] = {7, 10, 4, 3, 20, 15};
    printf("%d\n", findKthLargest(nums4, 6, 3)); // 10

    int nums5[] = {-1, -2, 0, 2};
    printf("%d\n", findKthLargest(nums5, 4, 2)); // 0

    return 0;
}