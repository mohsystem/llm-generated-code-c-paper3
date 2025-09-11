#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Descending order
}

int findKthLargest(int nums[], int numsSize, int k) {
    if (nums == NULL || numsSize <= 0 || k <= 0 || k > numsSize) {
         // Handle invalid input as appropriate in C. You might return a special value or print an error message.
        fprintf(stderr, "Invalid input\n");
        exit(1); // Or return an error code.
    }

    qsort(nums, numsSize, sizeof(int), compare);
    return nums[k - 1];
}

int main() {
    int test1[] = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    printf("%d\n", findKthLargest(test1, 6, k1)); // Output: 5

    int test2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    printf("%d\n", findKthLargest(test2, 9, k2)); // Output: 4

    int test3[] = {1};
    int k3 = 1;
    printf("%d\n", findKthLargest(test3, 1, k3)); // Output: 1

    int test4[] = {1, 2};
    int k4 = 2;
    printf("%d\n", findKthLargest(test4, 2, k4)); // Output: 1

    int test5[] = {2, 1};
    int k5 = 1;
    printf("%d\n", findKthLargest(test5, 2, k5)); // Output: 2


    return 0;
}