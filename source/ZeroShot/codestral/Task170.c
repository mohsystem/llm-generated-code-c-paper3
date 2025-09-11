#include <stdio.h>
#include <stdlib.h>

int countWhileMerging(long* sum, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    int mid = (start + end) / 2;
    int count = countWhileMerging(sum, start, mid, lower, upper)
                + countWhileMerging(sum, mid, end, lower, upper);
    int j = mid, k = mid, t = mid;
    long* cache = (long*)malloc(sizeof(long) * (end - start));
    for (int i = start, r = 0; i < mid; i++, r++) {
        while (k < end && sum[k] - sum[i] < lower) k++;
        while (j < end && sum[j] - sum[i] <= upper) j++;
        while (t < end && sum[t] < sum[i]) cache[r++] = sum[t++];
        count += j - k;
    }
    for (int i = start; i < t; i++) {
        sum[i] = cache[i - start];
    }
    for (int i = t; i < end; i++) {
        sum[i + start + t - mid] = sum[i];
    }
    free(cache);
    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long* sum = (long*)malloc(sizeof(long) * (numsSize + 1));
    sum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        sum[i + 1] = sum[i] + nums[i];
    }
    int count = countWhileMerging(sum, 0, numsSize + 1, lower, upper);
    free(sum);
    return count;
}

int main() {
    int nums1[] = {-2,5,-1};
    printf("%d\n", countRangeSum(nums1, 3, -2, 2)); // Output: 3
    int nums2[] = {0};
    printf("%d\n", countRangeSum(nums2, 1, 0, 0)); // Output: 1
    return 0;
}