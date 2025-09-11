#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}

int findKthLargest(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k <= 0 || k > numsSize) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    qsort(nums, numsSize, sizeof(int), cmpfunc);

    return nums[k - 1];
}

int main() {
    int nums[] = {3, 2, 1, 5, 6, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    printf("%d\n", findKthLargest(nums, numsSize, k)); // Outputs: 5
    return 0;
}