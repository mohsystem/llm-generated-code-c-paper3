#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    int xorValue = 0;
    for (int i = 0; i < numsSize; i++) {
        xorValue ^= nums[i];
    }
    return xorValue == 0 || numsSize % 2 == 0;
}

int main() {
    int testCases[][5] = {
        {1, 1, 2},
        {0, 1},
        {1, 2, 3},
        {3, 5, 6, 8},
        {1, 1, 1, 1}
    };
    int testSizes[] = {3, 2, 3, 4, 4};

    for (int i = 0; i < 5; i++) {
        printf("%s\n", xorGame(testCases[i], testSizes[i]) ? "true" : "false");
    }
    
    return 0;
}