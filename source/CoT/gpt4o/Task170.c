#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    if (*(long*)a < *(long*)b) return -1;
    if (*(long*)a > *(long*)b) return 1;
    return 0;
}

int countWhileMerging(long* prefixSums, int start, int end, int lower, int upper) {
    if (end - start <= 1) {
        return 0;
    }
    int mid = (start + end) / 2;
    int count = countWhileMerging(prefixSums, start, mid, lower, upper)
              + countWhileMerging(prefixSums, mid, end, lower, upper);
    
    int j = mid, k = mid;
    for (int left = start; left < mid; ++left) {
        while (j < end && prefixSums[j] - prefixSums[left] < lower) j++;
        while (k < end && prefixSums[k] - prefixSums[left] <= upper) k++;
        count += k - j;
    }

    qsort(prefixSums + start, end - start, sizeof(long), compare);
    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long* prefixSums = (long*)malloc((numsSize + 1) * sizeof(long));
    prefixSums[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }
    int result = countWhileMerging(prefixSums, 0, numsSize + 1, lower, upper);
    free(prefixSums);
    return result;
}

int main() {
    int nums1[] = {-2, 5, -1};
    printf("%d\n", countRangeSum(nums1, 3, -2, 2)); // 3
    int nums2[] = {0};
    printf("%d\n", countRangeSum(nums2, 1, 0, 0)); // 1
    int nums3[] = {1, -1};
    printf("%d\n", countRangeSum(nums3, 2, -1, 1)); // 3
    int nums4[] = {1, 2, 3, 4};
    printf("%d\n", countRangeSum(nums4, 4, 3, 8)); // 6
    int nums5[] = {0, 0, 0, 0, 0};
    printf("%d\n", countRangeSum(nums5, 5, 0, 0)); // 15
    return 0;
}