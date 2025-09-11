#include <stdio.h>
#include <stdlib.h>

void countSmaller(int* nums, int numsSize, int* result) {
    int* sortedList = (int*)malloc(numsSize * sizeof(int));
    int sortedSize = 0;
    
    for (int i = numsSize - 1; i >= 0; --i) {
        int left = 0, right = sortedSize;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (sortedList[mid] >= nums[i]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        for (int j = sortedSize; j > left; --j) {
            sortedList[j] = sortedList[j - 1];
        }
        sortedList[left] = nums[i];
        result[i] = left;
        ++sortedSize;
    }
    
    free(sortedList);
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int result1[4];
    countSmaller(nums1, 4, result1);
    for (int i = 0; i < 4; ++i) printf("%d ", result1[i]);
    printf("\n");
    
    int nums2[] = {-1};
    int result2[1];
    countSmaller(nums2, 1, result2);
    for (int i = 0; i < 1; ++i) printf("%d ", result2[i]);
    printf("\n");
    
    int nums3[] = {-1, -1};
    int result3[2];
    countSmaller(nums3, 2, result3);
    for (int i = 0; i < 2; ++i) printf("%d ", result3[i]);
    printf("\n");
    
    int nums4[] = {3, 4, 2, 7, 5};
    int result4[5];
    countSmaller(nums4, 5, result4);
    for (int i = 0; i < 5; ++i) printf("%d ", result4[i]);
    printf("\n");
    
    int nums5[] = {10, 9, 8, 7, 6};
    int result5[5];
    countSmaller(nums5, 5, result5);
    for (int i = 0; i < 5; ++i) printf("%d ", result5[i]);
    printf("\n");
    
    return 0;
}