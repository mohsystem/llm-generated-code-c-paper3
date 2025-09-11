
#include <stdio.h>
#include <stdlib.h>

int merge_sort(int* nums, int left, int right) {
    if (left >= right) return 0;
    
    int mid = left + (right - left) / 2;
    int count = merge_sort(nums, left, mid) + merge_sort(nums, mid + 1, right);
    
    // Count reverse pairs
    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && nums[i] > 2LL * nums[j]) {
            j++;
        }
        count += j - (mid + 1);
    }
    
    // Merge
    int* temp = (int*)malloc((right - left + 1) * sizeof(int));
    int i = left, k = mid + 1, p = 0;
    while (i <= mid && k <= right) {
        temp[p++] = nums[i] <= nums[k] ? nums[i++] : nums[k++];
    }
    while (i <= mid) temp[p++] = nums[i++];
    while (k <= right) temp[p++] = nums[k++];
    
    for (i = 0; i < right - left + 1; i++) {
        nums[left + i] = temp[i];
    }
    
    free(temp);
    return count;
}

int reversePairs(int* nums, int numsSize) {
    return merge_sort(nums, 0, numsSize - 1);
}

int main() {
    // Test case 1
    int nums1[] = {1,3,2,3,1};
    printf("%d\\n", reversePairs(nums1, 5));  // Expected: 2
    
    // Test case 2
    int nums2[] = {2,4,3,5,1};
    printf("%d\\n", reversePairs(nums2, 5));  // Expected: 3
    
    // Test case 3
    int nums3[] = {1,1,1,1,1};
    printf("%d\\n", reversePairs(nums3, 5));  // Expected: 0
    
    // Test case 4
    int nums4[] = {5,4,3,2,1};
    printf("%d\\n", reversePairs(nums4, 5));  // Expected: 4
    
    // Test case 5
    int nums5[] = {2147483647,2147483647,2147483647};
    printf("%d\\n", reversePairs(nums5, 3));  // Expected: 0
    
    return 0;
}
