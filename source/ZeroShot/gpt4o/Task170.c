#include <stdio.h>
#include <stdlib.h>

int countWhileMergeSort(long* sums, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    int mid = (start + end) / 2;
    int count = countWhileMergeSort(sums, start, mid, lower, upper) +
                countWhileMergeSort(sums, mid, end, lower, upper);
    int j = mid, k = mid, t = mid;
    long* cache = (long*)malloc((end - start) * sizeof(long));
    for (int i = start, r = 0; i < mid; ++i, ++r) {
        while (k < end && sums[k] - sums[i] < lower) k++;
        while (j < end && sums[j] - sums[i] <= upper) j++;
        while (t < end && sums[t] < sums[i]) cache[r++] = sums[t++];
        cache[r] = sums[i];
        count += j - k;
    }
    for (int i = 0; i < t - start; ++i) {
        sums[start + i] = cache[i];
    }
    free(cache);
    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    if (nums == NULL || numsSize == 0) return 0;
    long* prefixSums = (long*)malloc((numsSize + 1) * sizeof(long));
    prefixSums[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }
    int result = countWhileMergeSort(prefixSums, 0, numsSize + 1, lower, upper);
    free(prefixSums);
    return result;
}

int main() {
    int nums1[] = {-2, 5, -1};
    printf("%d\n", countRangeSum(nums1, 3, -2, 2)); // 3

    int nums2[] = {0};
    printf("%d\n", countRangeSum(nums2, 1, 0, 0)); // 1

    int nums3[] = {1, 2, 3, 4};
    printf("%d\n", countRangeSum(nums3, 4, 1, 3)); // 3

    int nums4[] = {3, 3, -1, -2};
    printf("%d\n", countRangeSum(nums4, 4, -3, 3)); // 7

    int nums5[] = {-2, -1, 0, 1, 2};
    printf("%d\n", countRangeSum(nums5, 5, -3, 1)); // 9

    return 0;
}