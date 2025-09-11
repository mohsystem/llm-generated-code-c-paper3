#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int mergeSort(int *nums, int left, int right) {
    if (left >= right) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);

    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && (long long)nums[i] > 2LL * nums[j]) {
            j++;
        }
        count += j - (mid + 1);
    }

    qsort(nums + left, right - left + 1, sizeof(int), compare);
    return count;
}

int reversePairs(int* nums, int numsSize){
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    int testCases[][5] = {
        {1, 3, 2, 3, 1},
        {2, 4, 3, 5, 1},
        {},
        {5, 4, 3, 2, 1},
        {1}
    };
    int testCaseSizes[] = {5, 5, 0, 5, 1};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", reversePairs(testCases[i], testCaseSizes[i]));
    }
    return 0;
}