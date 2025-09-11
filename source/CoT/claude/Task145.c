
#include <stdio.h>
#include <stdlib.h>

int maxSubArraySum(const int arr[], int size) {
    if (size <= 0) {
        return 0;
    }
    
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];
    
    for (int i = 1; i < size; i++) {
        maxEndingHere = (arr[i] > maxEndingHere + arr[i]) ? arr[i] : maxEndingHere + arr[i];
        maxSoFar = (maxSoFar > maxEndingHere) ? maxSoFar : maxEndingHere;
    }
    
    return maxSoFar;
}

int main() {
    // Test cases
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printf("Test 1: %d\\n", maxSubArraySum(arr1, 9)); // Expected: 6

    int arr2[] = {1};
    printf("Test 2: %d\\n", maxSubArraySum(arr2, 1)); // Expected: 1

    int arr3[] = {-1, -2, -3, -4};
    printf("Test 3: %d\\n", maxSubArraySum(arr3, 4)); // Expected: -1

    int arr4[] = {1, 2, 3, 4, 5};
    printf("Test 4: %d\\n", maxSubArraySum(arr4, 5)); // Expected: 15

    int arr5[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    printf("Test 5: %d\\n", maxSubArraySum(arr5, 8)); // Expected: 7

    return 0;
}
