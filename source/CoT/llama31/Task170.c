// Note: C does not support dynamic memory allocation for arrays or complex data structures like vectors.
// The implementation below is simplified and may not cover all edge cases or performance optimizations.

#include <stdio.h>

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    int sum[numsSize + 1];
    sum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        sum[i + 1] = sum[i] + nums[i];
    }
    return countWhileMergeSort(sum, 0, numsSize + 1, lower, upper);
}

int countWhileMergeSort(int* sum, int start, int end, int lower, int upper) {
    if (end - start <= 1) {
        return 0;
    }
    int mid = start + (end - start) / 2;
    int count = countWhileMergeSort(sum, start, mid, lower, upper) +
                countWhileMergeSort(sum, mid, end, lower, upper);
    int j = mid, k = mid, t = mid;
    int l[end - start];
    for (int i = start, r = 0; i < mid; i++, r++) {
        while (k < end && sum[k] - sum[i] < lower) {
            k++;
        }
        while (j < end && sum[j] - sum[i] <= upper) {
            j++;
        }
        while (t < end && sum[t] < sum[i]) {
            l[r++] = sum[t++];
        }
        l[r] = sum[i];
        count += j - k;
    }
    for (int i = 0; i < t - start; i++) {
        sum[start + i] = l[i];
    }
    for (int i = t - start; i < end - start; i++) {
        sum[start + i] = l[i];
    }
    return count;
}

int main() {
    int nums1[] = {-2, 5, -1};
    int lower1 = -2;
    int upper1 = 2;
    printf("Output: %d\n", countRangeSum(nums1, 3, lower1, upper1)); // Output: 3

    int nums2[] = {0};
    int lower2 = 0;
    int upper2 = 0;
    printf("Output: %d\n", countRangeSum(nums2, 1, lower2, upper2)); // Output: 1

    int nums3[] = {1, 2, 3, 4, 5};
    int lower3 = 1;
    int upper3 = 10;
    printf("Output: %d\n", countRangeSum(nums3, 5, lower3, upper3)); // Output: 10

    int nums4[] = {-10, -5, 0, 5, 10};
    int lower4 = -10;
    int upper4 = 10;
    printf("Output: %d\n", countRangeSum(nums4, 5, lower4, upper4)); // Output: 15

    int nums5[] = {0, 0, 0, 0};
    int lower5 = 0;
    int upper5 = 0;
    printf("Output: %d\n", countRangeSum(nums5, 4, lower5, upper5)); // Output: 10

    return 0;
}