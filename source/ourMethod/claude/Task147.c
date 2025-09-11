
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* nums, int left, int right) {
    int pivot = nums[right];
    int i = left;
    
    for (int j = left; j < right; j++) {
        if (nums[j] <= pivot) {
            swap(&nums[i], &nums[j]);
            i++;
        }
    }
    swap(&nums[i], &nums[right]);
    return i;
}

int quickSelect(int* nums, int left, int right, int k) {
    if (left == right) return nums[left];
    
    int pivotIndex = partition(nums, left, right);
    
    if (pivotIndex == k) return nums[k];
    else if (pivotIndex < k) return quickSelect(nums, pivotIndex + 1, right, k);
    else return quickSelect(nums, left, pivotIndex - 1, k);
}

int findKthLargest(int* nums, int size, int k) {
    if (nums == NULL || size == 0) {
        fprintf(stderr, "Array cannot be null or empty\\n");
        exit(1);
    }
    if (k <= 0 || k > size) {
        fprintf(stderr, "k must be between 1 and array length\\n");
        exit(1);
    }
    
    return quickSelect(nums, 0, size - 1, size - k);
}

int main() {
    // Test cases
    int test1[] = {3, 2, 1, 5, 6, 4};
    printf("%d\\n", findKthLargest(test1, 6, 2));  // Expected: 5
    
    int test2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    printf("%d\\n", findKthLargest(test2, 9, 4));  // Expected: 4
    
    int test3[] = {1};
    printf("%d\\n", findKthLargest(test3, 1, 1));  // Expected: 1
    
    int test4[] = {1, 2, 3, 4, 5};
    printf("%d\\n", findKthLargest(test4, 5, 1));  // Expected: 5
    
    int test5[] = {5, 5, 5, 5, 5};
    printf("%d\\n", findKthLargest(test5, 5, 2));  // Expected: 5
    
    return 0;
}
