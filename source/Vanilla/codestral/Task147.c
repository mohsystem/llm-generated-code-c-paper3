#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int findKthLargest(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    return nums[k - 1];
}

int main() {
    int nums[] = {3,2,1,5,6,4};
    int k = 2;
    printf("%d\n", findKthLargest(nums, 6, k));  // Output: 5
    return 0;
}