#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mergeSortAndCount(long long *sums, int start, int end, int lower, int upper);

int countRangeSum(int *nums, int numsSize, int lower, int upper) {
    int n = numsSize;
    long long *sums = (long long *)malloc((n + 1) * sizeof(long long));
    memset(sums, 0, (n+1) * sizeof(long long));
    for (int i = 0; i < n; ++i) {
        sums[i + 1] = sums[i] + nums[i];
    }
    int result = mergeSortAndCount(sums, 0, n + 1, lower, upper);
    free(sums);
    return result;
}

int mergeSortAndCount(long long *sums, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    int mid = (start + end) / 2;
    int count = mergeSortAndCount(sums, start, mid, lower, upper) +
                mergeSortAndCount(sums, mid, end, lower, upper);
    int j = mid, k = mid, t = mid;
    long long *cache = (long long *)malloc((end - start) * sizeof(long long));
    for (int i = start, r = 0; i < mid; ++i, ++r) {
        while (k < end && sums[k] - sums[i] < lower) k++;
        while (j < end && sums[j] - sums[i] <= upper) j++;
        while (t < end && sums[t] < sums[i]) cache[r++] = sums[t++];
        cache[r] = sums[i];
        count += j - k;
    }
    memcpy(sums + start, cache, (t - start) * sizeof(long long));
    free(cache);
    return count;
}

int main() {
    int nums1[] = {-2, 5, -1};
    int nums2[] = {0};
    int nums3[] = {1, 2, 3, 4, 5, 6, 7};
    int nums4[] = {0, 0};
    int nums5[] = {-2147483647, 0, -2147483647, 2147483647};

    printf("%d\n", countRangeSum(nums1, 3, -2, 2));
    printf("%d\n", countRangeSum(nums2, 1, 0, 0));
    printf("%d\n", countRangeSum(nums3, 7, 3, 6));
    printf("%d\n", countRangeSum(nums4, 2, 0, 0));
    printf("%d\n", countRangeSum(nums5, 4, -564, 3864));

    return 0;
}