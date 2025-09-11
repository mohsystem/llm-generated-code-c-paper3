
#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    if (numsSize % 2 == 0) return true;
    
    int xor_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_sum ^= nums[i];
    }
    return xor_sum == 0;
}

int main() {
    // Test cases
    int testCase1[] = {1, 1, 2};
    int testCase2[] = {0, 1};
    int testCase3[] = {1, 2, 3};
    int testCase4[] = {1, 2, 3, 4};
    int testCase5[] = {0, 0, 0};
    
    printf("Test case 1: %s\\n", xorGame(testCase1, 3) ? "true" : "false");
    printf("Test case 2: %s\\n", xorGame(testCase2, 2) ? "true" : "false");
    printf("Test case 3: %s\\n", xorGame(testCase3, 3) ? "true" : "false");
    printf("Test case 4: %s\\n", xorGame(testCase4, 4) ? "true" : "false");
    printf("Test case 5: %s\\n", xorGame(testCase5, 3) ? "true" : "false");
    
    return 0;
}
