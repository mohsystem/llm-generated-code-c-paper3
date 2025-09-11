
#include <stdio.h>

int findKthLargest(int nums[], int size, int k) {
    if (nums == NULL || size == 0 || k <= 0 || k > size) {
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
    
    return nums[k - 1];
}

int main() {
    // Test cases
    int test1[] = {3, 2, 1, 5, 6, 4};
    printf("Test 1: %d\\n", findKthLargest(test1, 6, 2)); // Expected: 5
    
    int test2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    printf("Test 2: %d\\n", findKthLargest(test2, 9, 4)); // Expected: 4
    
    int test3[] = {1};
    printf("Test 3: %d\\n", findKthLargest(test3, 1, 1)); // Expected: 1
    
    int test4[] = {7, 6, 5, 4, 3, 2, 1};
    printf("Test 4: %d\\n", findKthLargest(test4, 7, 3)); // Expected: 5
    
    int test5[] = {1, 2, 3, 4, 5};
    printf("Test 5: %d\\n", findKthLargest(test5, 5, 1)); // Expected: 5
    
    return 0;
}
