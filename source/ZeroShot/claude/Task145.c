
#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int arr[], int size) {
    if (size == 0) return 0;
    
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
    int test1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int test2[] = {1, 2, 3, 4, 5};
    int test3[] = {-1, -2, -3, -4};
    int test4[] = {1};
    int test5[] = {-2, 1};

    printf("Test 1: %d\\n", maxSubArraySum(test1, 9)); // Expected: 6
    printf("Test 2: %d\\n", maxSubArraySum(test2, 5)); // Expected: 15
    printf("Test 3: %d\\n", maxSubArraySum(test3, 4)); // Expected: -1
    printf("Test 4: %d\\n", maxSubArraySum(test4, 1)); // Expected: 1
    printf("Test 5: %d\\n", maxSubArraySum(test5, 2)); // Expected: 1

    return 0;
}
