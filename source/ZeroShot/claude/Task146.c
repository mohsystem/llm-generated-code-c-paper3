
#include <stdio.h>

int findMissing(int nums[], int size) {
    if (size == 0) return 1;
    
    int n = size + 1;
    int expectedSum = (n * (n + 1)) / 2;
    int actualSum = 0;
    
    for (int i = 0; i < size; i++) {
        actualSum += nums[i];
    }
    
    return expectedSum - actualSum;
}

int main() {
    // Test cases
    int test1[] = {1, 2, 4, 5}; // missing 3
    int test2[] = {1, 3, 4}; // missing 2
    int test3[] = {2, 3, 4, 5}; // missing 1
    int test4[] = {1, 2, 3, 5, 6}; // missing 4
    int test5[] = {1, 2, 3, 4, 6, 7}; // missing 5
    
    printf("Missing number: %d\\n", findMissing(test1, 4)); // 3
    printf("Missing number: %d\\n", findMissing(test2, 3)); // 2
    printf("Missing number: %d\\n", findMissing(test3, 4)); // 1
    printf("Missing number: %d\\n", findMissing(test4, 5)); // 4
    printf("Missing number: %d\\n", findMissing(test5, 6)); // 5
    
    return 0;
}
