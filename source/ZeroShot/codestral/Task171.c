#include <stdio.h>
#include <stdlib.h>

int reversePairs(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0) {
        return 0;
    }
    return mergeSort(nums, 0, numsSize - 1);
}

int mergeSort(int* nums, int start, int end) {
    if (start >= end) {
        return 0;
    }
    int mid = start + (end - start) / 2;
    int count = mergeSort(nums, start, mid) + mergeSort(nums, mid + 1, end);
    for (int i = start, j = mid + 1; i <= mid; i++) {
        while (j <= end && (long)nums[i] > 2 * (long)nums[j]) {
            j++;
        }
        count += j - (mid + 1);
    }
    int temp[end - start + 1];
    for (int i = start; i <= end; i++) {
        temp[i - start] = nums[i];
    }
    qsort(temp, end - start + 1, sizeof(int), compare);
    for (int i = start; i <= end; i++) {
        nums[i] = temp[i - start];
    }
    return count;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    printf("%d\n", reversePairs((int[]){1,3,2,3,1}, 5)); // Output: 2
    printf("%d\n", reversePairs((int[]){2,4,3,5,1}, 5)); // Output: 3
    return 0;
}