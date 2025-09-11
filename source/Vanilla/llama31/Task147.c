#include <stdio.h>

int findKthLargest(int nums[], int n, int k) {
    return quickSelect(nums, 0, n - 1, n - k);
}

int quickSelect(int nums[], int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }
    int pivotIndex = partition(nums, left, right);
    if (k == pivotIndex) {
        return nums[k];
    } else if (k < pivotIndex) {
        return quickSelect(nums, left, pivotIndex - 1, k);
    } else {
        return quickSelect(nums, pivotIndex + 1, right, k);
    }
}

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

int main() {
    int testCases[][7] = {
        {3, 2, 1, 5, 6, 4, 2},
        {10, 5, 4, 3, 48, 6, 2, 33, 53, 10, 4},
        {1, 2, 3, 4, 5, 1},
        {5, 4, 3, 2, 1, 3},
        {10, 20, 30, 40, 50, 5}
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < numTestCases; i++) {
        int n = sizeof(testCases[i]) / sizeof(testCases[i][0]) - 1;
        int k = testCases[i][n];
        printf("Kth Largest Element: %d\n", findKthLargest(testCases[i], n, k));
    }
    return 0;
}