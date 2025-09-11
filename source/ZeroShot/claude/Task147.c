
#include <stdio.h>

int findKthLargest(int nums[], int size, int k) {
    if (size == 0 || k < 1 || k > size) {
        return -1;
    }
    
    // Sort array in descending order
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (nums[j] < nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
    
    // Return kth element (1-based index)
    return nums[k - 1];
}

int main() {
    // Test case 1
    int arr1[] = {3, 2, 1, 5, 6, 4};
    printf("%d\\n", findKthLargest(arr1, 6, 2));  // Expected: 5

    // Test case 2
    int arr2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    printf("%d\\n", findKthLargest(arr2, 9, 4));  // Expected: 4

    // Test case 3
    int arr3[] = {1};
    printf("%d\\n", findKthLargest(arr3, 1, 1));  // Expected: 1

    // Test case 4
    int arr4[] = {7, 7, 7, 7, 7};
    printf("%d\\n", findKthLargest(arr4, 5, 3));  // Expected: 7

    // Test case 5
    int arr5[] = {9, 8, 7, 6, 5};
    printf("%d\\n", findKthLargest(arr5, 5, 1));  // Expected: 9

    return 0;
}
