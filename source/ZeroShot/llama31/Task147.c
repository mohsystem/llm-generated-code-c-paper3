#include <stdio.h>

int partition(int nums[], int left, int right) {
    int pivot = nums[right];
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (nums[i] < pivot) {
            int temp = nums[storeIndex];
            nums[storeIndex] = nums[i];
            nums[i] = temp;
            storeIndex++;
        }
    }
    int temp = nums[right];
    nums[right] = nums[storeIndex];
    nums[storeIndex] = temp;
    return storeIndex;
}

int quickSelect(int nums[], int left, int right, int kSmallest) {
    if (left == right) {
        return nums[left];
    }
    int pivotIndex = partition(nums, left, right);
    if (kSmallest == pivotIndex) {
        return nums[kSmallest];
    } else if (kSmallest < pivotIndex) {
        return quickSelect(nums, left, pivotIndex - 1, kSmallest);
    } else {
        return quickSelect(nums, pivotIndex + 1, right, kSmallest);
    }
}

int findKthLargest(int nums[], int n, int k) {
    return quickSelect(nums, 0, n - 1, n - k);
}

int main() {
    int nums[] = {3, 2, 1, 5, 6, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("Kth largest element: %d\n", findKthLargest(nums, n, 2));

    int nums2[] = {10, 9, 8, 7, 6, 5};
    n = sizeof(nums2) / sizeof(nums2[0]);
    printf("Kth largest element: %d\n", findKthLargest(nums2, n, 3));

    int nums3[] = {1, 2, 3, 4, 5};
    n = sizeof(nums3) / sizeof(nums3[0]);
    printf("Kth largest element: %d\n", findKthLargest(nums3, n, 1));

    int nums4[] = {5, 4, 3, 2, 1};
    n = sizeof(nums4) / sizeof(nums4[0]);
    printf("Kth largest element: %d\n", findKthLargest(nums4, n, 5));

    int nums5[] = {10, 20, 30, 40, 50};
    n = sizeof(nums5) / sizeof(nums5[0]);
    printf("Kth largest element: %d\n", findKthLargest(nums5, n, 4));

    return 0;
}