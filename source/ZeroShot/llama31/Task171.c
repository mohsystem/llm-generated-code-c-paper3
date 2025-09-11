#include <stdio.h>

int mergeSort(int nums[], int low, int high);
int merge(int nums[], int low, int mid, int high);

int countReversePairs(int nums[], int n) {
    return mergeSort(nums, 0, n - 1);
}

int mergeSort(int nums[], int low, int high) {
    if (low >= high) return 0;

    int mid = low + (high - low) / 2;
    int left = mergeSort(nums, low, mid);
    int right = mergeSort(nums, mid + 1, high);
    int merged = merge(nums, low, mid, high);

    return left + right + merged;
}

int merge(int nums[], int low, int mid, int high) {
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    int left[leftSize], right[rightSize];

    for (int i = 0; i < leftSize; i++) {
        left[i] = nums[low + i];
    }
    for (int i = 0; i < rightSize; i++) {
        right[i] = nums[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;
    int count = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] > 2 * right[j]) {
            count += leftSize - i;
            nums[k++] = right[j++];
        } else {
            nums[k++] = left[i++];
        }
    }

    while (i < leftSize) {
        nums[k++] = left[i++];
    }

    while (j < rightSize) {
        nums[k++] = right[j++];
    }

    return count;
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    printf("Reverse pairs: %d\n", countReversePairs(nums1, 5));

    int nums2[] = {2, 4, 3, 5, 1};
    printf("Reverse pairs: %d\n", countReversePairs(nums2, 5));

    int nums3[] = {1, 2, 3, 4, 5};
    printf("Reverse pairs: %d\n", countReversePairs(nums3, 5));

    int nums4[] = {5, 4, 3, 2, 1};
    printf("Reverse pairs: %d\n", countReversePairs(nums4, 5));

    int nums5[] = {1, 1, 1, 1, 1};
    printf("Reverse pairs: %d\n", countReversePairs(nums5, 5));

    return 0;
}