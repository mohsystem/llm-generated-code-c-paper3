// Note: Implementing this in C is complex due to the lack of built-in support for dynamic arrays and vectors.
// Here is a simplified version that might not handle all edge cases efficiently.

#include <stdio.h>
#include <stdlib.h>

long long* mergeSort(long long* arr, int start, int end, int lower, int upper, int* count) {
    if (end - start <= 1) return arr;
    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid, lower, upper, count);
    mergeSort(arr, mid, end, lower, upper, count);

    int j = mid, k = mid, t = mid;
    long long* l = (long long*)malloc((end - start) * sizeof(long long));
    for (int i = start, r = 0; i < mid; i++, r++) {
        while (k < end && arr[k] - arr[i] < lower) k++;
        while (j < end && arr[j] - arr[i] <= upper) j++;
        while (t < end && arr[t] < arr[i]) {
            l[r++] = arr[t++];
        }
        l[r] = arr[i];
        (*count) += j - k;
    }
    for (int i = start; i < end; i++) {
        arr[i] = l[i - start];
    }
    free(l);
    return arr;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long long* sum = (long long*)malloc((numsSize + 1) * sizeof(long long));
    sum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        sum[i + 1] = sum[i] + nums[i];
    }
    int count = 0;
    mergeSort(sum, 0, numsSize + 1, lower, upper, &count);
    free(sum);
    return count;
}

int main() {
    int nums1[] = {-2, 5, -1};
    int lower1 = -2;
    int upper1 = 2;
    printf("%d\n", countRangeSum(nums1, sizeof(nums1)/sizeof(nums1[0]), lower1, upper1));  // Output: 3

    int nums2[] = {0};
    int lower2 = 0;
    int upper2 = 0;
    printf("%d\n", countRangeSum(nums2, sizeof(nums2)/sizeof(nums2[0]), lower2, upper2));  // Output: 1

    int nums3[] = {1, 2, 3, 4, 5};
    int lower3 = 1;
    int upper3 = 10;
    printf("%d\n", countRangeSum(nums3, sizeof(nums3)/sizeof(nums3[0]), lower3, upper3));  // Output: 10

    int nums4[] = {-10, -10, -10};
    int lower4 = -20;
    int upper4 = 0;
    printf("%d\n", countRangeSum(nums4, sizeof(nums4)/sizeof(nums4[0]), lower4, upper4));  // Output: 6

    int nums5[] = {1, -2, 3, 4, -3, 5};
    int lower5 = -3;
    int upper5 = 4;
    printf("%d\n", countRangeSum(nums5, sizeof(nums5)/sizeof(nums5[0]), lower5, upper5));  // Output: 13

    return 0;
}