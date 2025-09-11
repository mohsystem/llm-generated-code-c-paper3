#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int mergeSort(int* nums, int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right) / 2;
    int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);
    for (int i = left, j = mid + 1; i <= mid; i++) {
        while (j <= right && (long)nums[i] > 2 * (long)nums[j]) j++;
        count += j - (mid + 1);
    }
    qsort(nums + left, right - left + 1, sizeof(int), cmp);
    return count;
}

int reversePairs(int* nums, int numsSize) {
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    int nums1[] = {1,3,2,3,1};
    printf("%d\n", reversePairs(nums1, 5)); // Output: 2
    int nums2[] = {2,4,3,5,1};
    printf("%d\n", reversePairs(nums2, 5)); // Output: 3
    return 0;
}