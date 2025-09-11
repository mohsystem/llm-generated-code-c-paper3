#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int mergeSort(int *nums, int left, int right) {
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

    qsort(nums + left, right - left + 1, sizeof(int), cmpfunc);
    return count;
}

int reversePairs(int* nums, int numsSize){
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int result1 = reversePairs(nums1, 5);
    printf("Test case 1: %d\n", result1); // Output: 2

    int nums2[] = {2, 4, 3, 5, 1};
    int result2 = reversePairs(nums2, 5);
    printf("Test case 2: %d\n", result2); // Output: 3

    int nums3[] = {};
    int result3 = reversePairs(nums3, 0);
    printf("Test case 3: %d\n", result3); // Output: 0

    int nums4[] = {1};
    int result4 = reversePairs(nums4, 1);
    printf("Test case 4: %d\n", result4); // Output: 0

    int nums5[] = {2147483647, -2147483648};
    int result5 = reversePairs(nums5, 2);
    printf("Test case 5: %d\n", result5); // Output: 1

    return 0;
}