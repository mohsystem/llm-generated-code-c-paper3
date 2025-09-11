#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(long *)a > *(long *)b) - (*(long *)a < *(long *)b);
}

int count_while_merging(long *sums, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    int mid = (start + end) / 2;
    int count = count_while_merging(sums, start, mid, lower, upper) +
                count_while_merging(sums, mid, end, lower, upper);
    int j = mid, k = mid;
    for (int i = start; i < mid; ++i) {
        while (k < end && sums[k] - sums[i] < lower) k++;
        while (j < end && sums[j] - sums[i] <= upper) j++;
        count += j - k;
    }
    qsort(sums + start, end - start, sizeof(long), compare);
    return count;
}

int countRangeSum(int *nums, int numsSize, int lower, int upper) {
    long *prefix_sums = (long *)malloc((numsSize + 1) * sizeof(long));
    if (!prefix_sums) return 0;
    prefix_sums[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + nums[i];
    }
    int result = count_while_merging(prefix_sums, 0, numsSize + 1, lower, upper);
    free(prefix_sums);
    return result;
}

int main() {
    int nums1[] = {-2, 5, -1};
    printf("%d\n", countRangeSum(nums1, 3, -2, 2)); // 3

    int nums2[] = {0};
    printf("%d\n", countRangeSum(nums2, 1, 0, 0)); // 1

    int nums3[] = {3, -1, 2, -4};
    printf("%d\n", countRangeSum(nums3, 4, -3, 1)); // 4

    int nums4[] = {1, 2, 3, 4};
    printf("%d\n", countRangeSum(nums4, 4, 0, 5)); // 3

    int nums5[] = {0, 0, 0, 0};
    printf("%d\n", countRangeSum(nums5, 4, 0, 0)); // 10

    return 0;
}