#include <stdio.h>
#include <stdlib.h>

int mergeSort(long long* arr, int start, int end, int lower, int upper, int* count) {
    if (end - start <= 1) return 0;
    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid, lower, upper, count);
    mergeSort(arr, mid, end, lower, upper, count);
    int* temp = (int*)malloc((end - start) * sizeof(int));
    int tIndex = 0;
    int l = start, r = mid;
    while (l < mid && r < end) {
        if (arr[l] <= arr[r]) {
            temp[tIndex++] = arr[l++];
        } else {
            temp[tIndex++] = arr[r++];
        }
    }
    while (l < mid) {
        temp[tIndex++] = arr[l++];
    }
    while (r < end) {
        temp[tIndex++] = arr[r++];
    }
    for (int i = start; i < end; i++) {
        arr[i] = temp[i - start];
    }
    free(temp);
    int left = start, right = start;
    int c1 = start, c2 = start;
    while (right < end) {
        while (c1 < mid && arr[c1] - arr[right] < lower) c1++;
        while (c2 < mid && arr[c2] - arr[right] <= upper) c2++;
        (*count) += c2 - c1;
        right++;
    }
    return *count;
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
    int nums[] = {-2, 5, -1};
    int lower = -2;
    int upper = 2;
    printf("Output: %d\n", countRangeSum(nums, 3, lower, upper));  // Output: 3

    int nums2[] = {0};
    lower = 0;
    upper = 0;
    printf("Output: %d\n", countRangeSum(nums2, 1, lower, upper));  // Output: 1
    return 0;
}