
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
    int test1[] = {1,1,2};
    int test2[] = {0,1};
    int test3[] = {1,2,3};
    int test4[] = {1,2,3,4};
    int test5[] = {1,1,1,1,1};
    
    printf("%s\\n", xorGame(test1, 3) ? "true" : "false");  // false
    printf("%s\\n", xorGame(test2, 2) ? "true" : "false");  // true
    printf("%s\\n", xorGame(test3, 3) ? "true" : "false");  // true
    printf("%s\\n", xorGame(test4, 4) ? "true" : "false");  // true
    printf("%s\\n", xorGame(test5, 5) ? "true" : "false");  // false
    
    return 0;
}
