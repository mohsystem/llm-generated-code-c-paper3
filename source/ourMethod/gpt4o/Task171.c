#include <stdio.h>
#include <stdlib.h>

int mergeAndCount(int* nums, int left, int mid, int right) {
    int* temp = (int*)malloc((right - left + 1) * sizeof(int));
    int i = left, j = mid + 1, k = 0, count = 0;
    while (i <= mid && j <= right) {
        if (nums[i] > 2LL * nums[j]) {
            count += mid - i + 1;
            j++;
        } else {
            i++;
        }
    }
    i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = nums[i++];
    }
    while (j <= right) {
        temp[k++] = nums[j++];
    }
    for (i = left; i <= right; i++) {
        nums[i] = temp[i - left];
    }
    free(temp);
    return count;
}

int mergeSortAndCount(int* nums, int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    int count = mergeSortAndCount(nums, left, mid) + mergeSortAndCount(nums, mid + 1, right);
    count += mergeAndCount(nums, left, mid, right);
    return count;
}

int reversePairs(int* nums, int numsSize) {
    return mergeSortAndCount(nums, 0, numsSize - 1);
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int nums2[] = {2, 4, 3, 5, 1};
    int nums3[] = {5, 4, 3, 2, 1};
    int nums4[] = {1, 1, 1, 1, 1};
    int nums5[] = {10, 20, 30, 40, 50};
    
    printf("%d\n", reversePairs(nums1, 5)); // Output: 2
    printf("%d\n", reversePairs(nums2, 5)); // Output: 3
    printf("%d\n", reversePairs(nums3, 5)); // Output: 4
    printf("%d\n", reversePairs(nums4, 5)); // Output: 0
    printf("%d\n", reversePairs(nums5, 5)); // Output: 0
    
    return 0;
}