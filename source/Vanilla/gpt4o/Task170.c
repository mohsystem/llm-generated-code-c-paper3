#include <stdio.h>
#include <stdlib.h>

int countWhileMergeSort(long* sums, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    int mid = (start + end) / 2;
    int count = countWhileMergeSort(sums, start, mid, lower, upper) 
              + countWhileMergeSort(sums, mid, end, lower, upper);
    long* cache = (long*)malloc((end - start) * sizeof(long));
    int j = mid, k = mid, t = mid, r = 0;
    for (int i = start; i < mid; ++i) {
        while (j < end && sums[j] - sums[i] < lower) j++;
        while (k < end && sums[k] - sums[i] <= upper) k++;
        while (t < end && sums[t] < sums[i]) cache[r++] = sums[t++];
        cache[r++] = sums[i];
        count += k - j;
    }
    for (int i = 0; i < r; ++i) {
        sums[start + i] = cache[i];
    }
    free(cache);
    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long* sums = (long*)malloc((numsSize + 1) * sizeof(long));
    sums[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        sums[i + 1] = sums[i] + nums[i];
    }
    int result = countWhileMergeSort(sums, 0, numsSize + 1, lower, upper);
    free(sums);
    return result;
}

int main() {
    int nums1[] = {-2, 5, -1};
    int nums2[] = {0};
    int nums3[] = {1, -1, 1};
    int nums4[] = {-1, -1, 1};
    int nums5[] = {3, 3, -2, 5, 1};
    printf("%d\n", countRangeSum(nums1, 3, -2, 2)); // Output: 3
    printf("%d\n", countRangeSum(nums2, 1, 0, 0)); // Output: 1
    printf("%d\n", countRangeSum(nums3, 3, 0, 2)); // Output: 4
    printf("%d\n", countRangeSum(nums4, 3, -2, -1)); // Output: 3
    printf("%d\n", countRangeSum(nums5, 5, 2, 4)); // Output: 3
    return 0;
}