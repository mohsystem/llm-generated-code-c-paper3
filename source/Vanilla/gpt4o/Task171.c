#include <stdio.h>
#include <stdlib.h>

int merge(int* nums, int* temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left, count = 0;

    while (i <= mid && j <= right) {
        if (nums[i] > 2LL * nums[j]) {
            count += mid - i + 1;
            j++;
        } else {
            i++;
        }
    }

    i = left;
    j = mid + 1;

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
        nums[i] = temp[i];
    }

    return count;
}

int mergeSort(int* nums, int* temp, int left, int right) {
    if (left >= right) return 0;

    int mid = (left + right) / 2;
    int count = mergeSort(nums, temp, left, mid) + mergeSort(nums, temp, mid + 1, right);

    count += merge(nums, temp, left, mid, right);

    return count;
}

int reversePairs(int* nums, int numsSize) {
    int* temp = (int*)malloc(numsSize * sizeof(int));
    int result = mergeSort(nums, temp, 0, numsSize - 1);
    free(temp);
    return result;
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int nums2[] = {2, 4, 3, 5, 1};
    int nums3[] = {5, 4, 3, 2, 1};
    int nums4[] = {1, 2, 3, 4, 5};
    int nums5[] = {2, 2, 2, 2, 2};

    printf("%d\n", reversePairs(nums1, 5)); // 2
    printf("%d\n", reversePairs(nums2, 5)); // 3
    printf("%d\n", reversePairs(nums3, 5)); // 4
    printf("%d\n", reversePairs(nums4, 5)); // 0
    printf("%d\n", reversePairs(nums5, 5)); // 0

    return 0;
}