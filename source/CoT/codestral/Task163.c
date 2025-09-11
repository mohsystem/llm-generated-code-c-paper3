#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int longestRun(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    qsort(nums, numsSize, sizeof(int), cmp);
    int maxLength = 1, currentLength = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1] + 1) {
            currentLength++;
            maxLength = (maxLength > currentLength) ? maxLength : currentLength;
        } else if (nums[i] != nums[i - 1]) {
            currentLength = 1;
        }
    }
    return maxLength;
}

int main() {
    int arr1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    printf("%d\n", longestRun(arr1, sizeof(arr1) / sizeof(arr1[0]))); // 5
    int arr2[] = {1, 2, 3, 10, 11, 15};
    printf("%d\n", longestRun(arr2, sizeof(arr2) / sizeof(arr2[0]))); // 3
    int arr3[] = {5, 4, 2, 1};
    printf("%d\n", longestRun(arr3, sizeof(arr3) / sizeof(arr3[0]))); // 2
    int arr4[] = {3, 5, 7, 10, 15};
    printf("%d\n", longestRun(arr4, sizeof(arr4) / sizeof(arr4[0]))); // 1
    return 0;
}