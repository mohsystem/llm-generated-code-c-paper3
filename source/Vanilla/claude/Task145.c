
#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int arr[], int size) {
    int max_so_far = arr[0];
    int curr_max = arr[0];
    
    for(int i = 1; i < size; i++) {
        curr_max = (arr[i] > curr_max + arr[i]) ? arr[i] : curr_max + arr[i];
        max_so_far = (max_so_far > curr_max) ? max_so_far : curr_max;
    }
    return max_so_far;
}

int main() {
    // Test cases
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int arr2[] = {1, 2, 3, -2, 5};
    int arr3[] = {-1, -2, -3, -4};
    int arr4[] = {1};
    int arr5[] = {-2, 1};
    
    printf("Test case 1: %d\\n", maxSubArraySum(arr1, 9)); // Expected output: 6
    printf("Test case 2: %d\\n", maxSubArraySum(arr2, 5)); // Expected output: 9
    printf("Test case 3: %d\\n", maxSubArraySum(arr3, 4)); // Expected output: -1
    printf("Test case 4: %d\\n", maxSubArraySum(arr4, 1)); // Expected output: 1
    printf("Test case 5: %d\\n", maxSubArraySum(arr5, 2)); // Expected output: 1
    
    return 0;
}
