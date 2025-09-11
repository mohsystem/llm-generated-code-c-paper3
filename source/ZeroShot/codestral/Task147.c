#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int findKthLargest(int* nums, int numsSize, int k) {
    if (k < 1 || k > numsSize) {
        fprintf(stderr, "Invalid value of k\n");
        exit(EXIT_FAILURE);
    }
    qsort(nums, numsSize, sizeof(int), compare);
    return nums[k - 1];
}

int main() {
    int nums[] = {3, 2, 1, 5, 6, 4};
    int k = 2;
    printf("%d\n", findKthLargest(nums, sizeof(nums)/sizeof(nums[0]), k));  // Output: 5
    return 0;
}