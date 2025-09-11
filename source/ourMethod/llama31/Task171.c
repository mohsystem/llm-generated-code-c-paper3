#include <stdio.h>

int merge(int* nums, int low, int mid, int high) {
    int count = 0;
    int temp[high - low + 1];
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high) {
        if (nums[i] > 2L * nums[j]) {
            count += mid - i + 1;
            temp[k++] = nums[j++];
        } else {
            temp[k++] = nums[i++];
        }
    }

    while (i <= mid) temp[k++] = nums[i++];
    while (j <= high) temp[k++] = nums[j++];

    for (int i = low; i <= high; ++i) {
        nums[i] = temp[i - low];
    }
    return count;
}

int mergeSort(int* nums, int low, int high) {
    if (low >= high) return 0;
    int mid = low + (high - low) / 2;
    int left = mergeSort(nums, low, mid);
    int right = mergeSort(nums, mid + 1, high);
    return left + right + merge(nums, low, mid, high);
}

int countReversePairs(int* nums, int n) {
    return mergeSort(nums, 0, n - 1);
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int nums2[] = {2, 4, 3, 5, 1};
    int nums3[] = {1, 2, 3, 4, 5};
    int nums4[] = {5, 4, 3, 2, 1};
    int nums5[] = {1, 1, 1, 1, 1};

    printf("Reverse pairs in nums1: %d\n", countReversePairs(nums1, 5));
    printf("Reverse pairs in nums2: %d\n", countReversePairs(nums2, 5));
    printf("Reverse pairs in nums3: %d\n", countReversePairs(nums3, 5));
    printf("Reverse pairs in nums4: %d\n", countReversePairs(nums4, 5));
    printf("Reverse pairs in nums5: %d\n", countReversePairs(nums5, 5));

    return 0;
}