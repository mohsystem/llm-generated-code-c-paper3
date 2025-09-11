#include <stdlib.h>

int mergeSort(int* nums, int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);
    for (int i = left, j = mid + 1; i <= mid; i++) {
        while (j <= right && (long)nums[i] > 2 * (long)nums[j]) j++;
        count += j - (mid + 1);
    }
    int* sorted = (int*)malloc(sizeof(int) * (right - left + 1));
    int k = 0, p1 = left, p2 = mid + 1;
    while (p1 <= mid && p2 <= right) {
        if (nums[p1] <= nums[p2]) sorted[k++] = nums[p1++];
        else sorted[k++] = nums[p2++];
    }
    while (p1 <= mid) sorted[k++] = nums[p1++];
    while (p2 <= right) sorted[k++] = nums[p2++];
    for (int i = left; i <= right; i++) nums[i] = sorted[i - left];
    free(sorted);
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 1) return 0;
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int nums2[] = {2, 4, 3, 5, 1};
    printf("%d\n", reversePairs(nums1, sizeof(nums1) / sizeof(nums1[0])));  // Output: 2
    printf("%d\n", reversePairs(nums2, sizeof(nums2) / sizeof(nums2[0])));  // Output: 3
    return 0;
}