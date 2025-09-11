
#include <stdio.h>
#include <stdbool.h>

bool xorGame(const int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0) {
        return false;
    }
    
    if (numsSize % 2 == 0) {
        return true;
    }
    
    int xor_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_sum ^= nums[i];
    }
    
    return xor_sum == 0;
}

int main() {
    // Test cases
    int test1[] = {1, 1, 2};
    int test2[] = {0, 1};
    int test3[] = {1, 2, 3};
    int test4[] = {1, 2, 3, 4};
    int test5[] = {0, 0, 0};
    
    printf("Test case 1: %s\\n", xorGame(test1, 3) ? "true" : "false");
    printf("Test case 2: %s\\n", xorGame(test2, 2) ? "true" : "false");
    printf("Test case 3: %s\\n", xorGame(test3, 3) ? "true" : "false");
    printf("Test case 4: %s\\n", xorGame(test4, 4) ? "true" : "false");
    printf("Test case 5: %s\\n", xorGame(test5, 3) ? "true" : "false");
    
    return 0;
}
