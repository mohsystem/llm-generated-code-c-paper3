#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    return xor == 0 || numsSize % 2 == 0;
}

int main() {
    int testCase1[] = {1, 1, 2};
    int testCase2[] = {0, 1};
    int testCase3[] = {1, 2, 3};
    int testCase4[] = {4, 5, 6, 7};
    int testCase5[] = {0};

    printf("%d\n", xorGame(testCase1, 3));
    printf("%d\n", xorGame(testCase2, 2));
    printf("%d\n", xorGame(testCase3, 3));
    printf("%d\n", xorGame(testCase4, 4));
    printf("%d\n", xorGame(testCase5, 1));

    return 0;
}