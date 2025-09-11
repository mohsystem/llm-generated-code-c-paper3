
#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int findKthLargest(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    return nums[numsSize - k];
}

int main() {
    // Test case 1
    int arr1[] = {3, 2, 1, 5, 6, 4};
    printf("%d\\n", findKthLargest(arr1, 6, 2)); // Expected: 5
    
    // Test case 2
    int arr2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    printf("%d\\n", findKthLargest(arr2, 9, 4)); // Expected: 4
    
    // Test case 3
    int arr3[] = {1};
    printf("%d\\n", findKthLargest(arr3, 1, 1)); // Expected: 1
    
    // Test case 4
    int arr4[] = {7, 6, 5, 4, 3, 2, 1};
    printf("%d\\n", findKthLargest(arr4, 7, 3)); // Expected: 5
    
    // Test case 5
    int arr5[] = {-1, -2, 0, 3, 1};
    printf("%d\\n", findKthLargest(arr5, 5, 1)); // Expected: 3
    
    return 0;
}
