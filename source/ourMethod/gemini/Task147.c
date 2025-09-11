#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Descending order
}

int findKthLargest(int nums[], int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k <= 0 || k > numsSize) {
         // Handle invalid input
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE); 
    }

    qsort(nums, numsSize, sizeof(int), compare);

    return nums[k - 1];
}

int main() {
    int test1[] = {3, 2, 1, 5, 6, 4};
    printf("%d\n", findKthLargest(test1, 6, 2)); // Expected 5

    int test2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    printf("%d\n", findKthLargest(test2, 9, 4)); // Expected 4

    int test3[] = {1};
    printf("%d\n", findKthLargest(test3, 1, 1)); // Expected 1

    int test4[] = {1,2};
    printf("%d\n", findKthLargest(test4, 2, 1)); // Expected 2

    int test5[] = {4, 2, 7, 1, 9, 5};
    printf("%d\n", findKthLargest(test5, 6, 3)); // Expected 5
    return 0;
}