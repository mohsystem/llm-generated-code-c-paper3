
#include <stdio.h>
#include <stdlib.h>

int merge(int* nums, int start, int mid, int end) {
    int* temp = (int*)malloc((end - start + 1) * sizeof(int));
    int i = start, j = mid + 1, k = 0;
    
    while (i <= mid && j <= end) {
        temp[k++] = nums[i] <= nums[j] ? nums[i++] : nums[j++];
    }
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= end) temp[k++] = nums[j++];
    
    for (i = 0; i < k; i++) {
        nums[start + i] = temp[i];
    }
    
    free(temp);
    return 0;
}

int mergeSort(int* nums, int start, int end) {
    if (start >= end) return 0;
    
    int mid = start + (end - start) / 2;
    int count = mergeSort(nums, start, mid) + mergeSort(nums, mid + 1, end);
    
    // Count reverse pairs
    int j = mid + 1;
    for (int i = start; i <= mid; i++) {
        while (j <= end && nums[i] > 2LL * nums[j]) {
            j++;
        }
        count += j - (mid + 1);
    }
    
    merge(nums, start, mid, end);
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (nums == NULL || numsSize < 2) return 0;
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    // Test case 1
    int nums1[] = {1, 3, 2, 3, 1};
    printf("%d\\n", reversePairs(nums1, 5));  // Expected: 2
    
    // Test case 2
    int nums2[] = {2, 4, 3, 5, 1};
    printf("%d\\n", reversePairs(nums2, 5));  // Expected: 3
    
    // Test case 3
    int nums3[] = {1, 1, 1, 1};
    printf("%d\\n", reversePairs(nums3, 4));  // Expected: 0
    
    // Test case 4
    int nums4[] = {5, 4, 3, 2, 1};
    printf("%d\\n", reversePairs(nums4, 5));  // Expected: 4
    
    // Test case 5
    int nums5[] = {2147483647, 2147483647, 2147483647};
    printf("%d\\n", reversePairs(nums5, 3));  // Expected: 0
    
    return 0;
}
