#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int findKthLargest(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k <= 0 || k > numsSize) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    qsort(nums, numsSize, sizeof(int), compare);
    return nums[k - 1];
}

int main() {
    int nums1[] = {3, 2, 1, 5, 6, 4};
    printf("%d\n", findKthLargest(nums1, 6, 2));  // Output: 5

    int nums2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    printf("%d\n", findKthLargest(nums2, 9, 4));  // Output: 4

    int nums3[] = {1};
    printf("%d\n", findKthLargest(nums3, 1, 1));  // Output: 1

    int nums4[] = {2, 1};
    printf("%d\n", findKthLargest(nums4, 2, 2));  // Output: 1

    int nums5[] = {7, 6, 5, 4, 3, 2, 1};
    printf("%d\n", findKthLargest(nums5, 7, 3));  // Output: 5

    return 0;
}