
#include <stdio.h>

int findMissingNumber(int arr[], int size) {
    if (size == 0) {
        return 1;
    }
    
    int n = size + 1;
    long long expectedSum = ((long long)n * (n + 1)) / 2;
    long long actualSum = 0;
    
    for (int i = 0; i < size; i++) {
        actualSum += arr[i];
    }
    
    return (int)(expectedSum - actualSum);
}

int main() {
    // Test cases
    int test1[] = {1, 2, 4, 5};  // missing 3
    int test2[] = {1, 3, 4, 5};  // missing 2
    int test3[] = {2, 3, 4, 5};  // missing 1
    int test4[] = {1, 2, 3, 5};  // missing 4
    int test5[] = {1, 2, 3, 4};  // missing 5
    
    printf("Missing number in test1: %d\\n", findMissingNumber(test1, 4));
    printf("Missing number in test2: %d\\n", findMissingNumber(test2, 4));
    printf("Missing number in test3: %d\\n", findMissingNumber(test3, 4));
    printf("Missing number in test4: %d\\n", findMissingNumber(test4, 4));
    printf("Missing number in test5: %d\\n", findMissingNumber(test5, 4));
    
    return 0;
}
