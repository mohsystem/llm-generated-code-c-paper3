
#include <stdio.h>
#include <stdlib.h>

int merge(int* nums, int start, int mid, int end) {
    int len = end - start + 1;
    int* temp = (int*)malloc(len * sizeof(int));
    int i = start, j = mid + 1, k = 0;
    
    while (i <= mid && j <= end) {
        if (nums[i] <= nums[j]) temp[k++] = nums[i++];
        else temp[k++] = nums[j++];
    }
    
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= end) temp[k++] = nums[j++];
    
    for (i = 0; i < len; i++) {
        nums[start + i] = temp[i];
    }
    
    free(temp);
    return 0;
}

int mergeSort(int* nums, int start, int end) {
    if (start >= end) return 0;
    
    int mid = start + (end - start) / 2;
    int count = mergeSort(nums, start, mid) + mergeSort(nums, mid + 1, end);
    
    for (int i = start, j = mid + 1; i <= mid; i++) {
        while (j <= end && nums[i] > 2LL * nums[j]) j++;
        count += j - (mid + 1);
    }
    
    merge(nums, start, mid, end);
    return count;
}

int reversePairs(int* nums, int numsSize) {
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    int test1[] = {1,3,2,3,1};
    int test2[] = {2,4,3,5,1};
    int test3[] = {1,1,1,1,1};
    int test4[] = {5,4,3,2,1};
    int test5[] = {1};
    
    printf("Test case 1: %d\\n", reversePairs(test1, 5));
    printf("Test case 2: %d\\n", reversePairs(test2, 5));
    printf("Test case 3: %d\\n", reversePairs(test3, 5));
    printf("Test case 4: %d\\n", reversePairs(test4, 5));
    printf("Test case 5: %d\\n", reversePairs(test5, 1));
    
    return 0;
}
