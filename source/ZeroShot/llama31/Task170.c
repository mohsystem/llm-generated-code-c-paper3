#include <stdio.h>
#include <stdlib.h>

int mergeSort(long long prefix[], int start, int end, int lower, int upper, int* count) {
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort(prefix, start, mid, lower, upper, count);
    mergeSort(prefix, mid + 1, end, lower, upper, count);
    mergeIt(prefix, start, mid, end, lower, upper, count);
}

void mergeIt(long long prefix[], int start, int mid, int end, int lower, int upper, int* count) {
    int j = mid + 1, k = mid + 1;
    for (int i = start; i <= mid; i++) {
        while (k <= end && prefix[k] - prefix[i] < lower) k++;
        while (j <= end && prefix[j] - prefix[i] <= upper) j++;
        *count += j - k;
    }
    merge(prefix, start, mid, end);
}

void merge(long long prefix[], int start, int mid, int end) {
    long long temp[end - start + 1];
    int i = start, j = mid + 1, k = 0;
    while (i <= mid && j <= end) {
        if (prefix[i] <= prefix[j]) temp[k++] = prefix[i++];
        else temp[k++] = prefix[j++];
    }
    while (i <= mid) temp[k++] = prefix[i++];
    while (j <= end) temp[k++] = prefix[j++];
    for (int i = 0; i < k; i++) prefix[start + i] = temp[i];
}

int countRangeSum(int nums[], int n, int lower, int upper) {
    long long prefix[n + 1];
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    int count = 0;
    mergeSort(prefix, 0, n, lower, upper, &count);
    return count;
}

int main() {
    int nums1[] = {-2, 5, -1};
    printf("%d\n", countRangeSum(nums1, 3, -2, 2));  // Output: 3

    int nums2[] = {0};
    printf("%d\n", countRangeSum(nums2, 1, 0, 0));  // Output: 1

    int nums3[] = {-3, 6, -1};
    printf("%d\n", countRangeSum(nums3, 3, -2, 2));  // Output: 2

    int nums4[] = {1, 2, 3, 4, 5};
    printf("%d\n", countRangeSum(nums4, 5, 3, 7));  // Output: 5

    int nums5[] = {-10, 10, -10, 10};
    printf("%d\n", countRangeSum(nums5, 4, -20, 20));  // Output: 10

    return 0;
}