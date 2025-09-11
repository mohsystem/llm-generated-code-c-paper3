#include <stdio.h>
#include <stdlib.h>

int merge(int* nums, int left, int mid, int right) {
    int count = 0;
    int* temp = (int*)malloc((right - left + 1) * sizeof(int));
    int i = left, j = mid + 1, k = 0;

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

int mergeSort(int* nums, int left, int right) {
    if (left >= right) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);

    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && nums[i] > 2LL * nums[j]) {
            j++;
        }
        count += j - (mid + 1);
    }

    merge(nums, left, mid, right);
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (nums == NULL || numsSize < 2) {
        return 0;
    }
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    int test1[] = {1, 3, 2, 3, 1};
    int test2[] = {2, 4, 3, 5, 1};
    int test3[] = {5, 4, 3, 2, 1};
    int test4[] = {1, 10, 100, 1000, 10000};
    int test5[] = {5, 8, 9, 3, 2};

    printf("%d\n", reversePairs(test1, 5)); // 2
    printf("%d\n", reversePairs(test2, 5)); // 3
    printf("%d\n", reversePairs(test3, 5)); // 0
    printf("%d\n", reversePairs(test4, 5)); // 0
    printf("%d\n", reversePairs(test5, 5)); // 4

    return 0;
}