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
    int test1[] = {1, 1, 2};
    int test2[] = {0, 1};
    int test3[] = {1, 2, 3};
    int test4[] = {1, 1};
    int test5[] = {1, 1, 1};

    printf("%d\n", xorGame(test1, 3)); // false
    printf("%d\n", xorGame(test2, 2)); // true
    printf("%d\n", xorGame(test3, 3)); // true
    printf("%d\n", xorGame(test4, 2)); // true
    printf("%d\n", xorGame(test5, 3)); // false

    return 0;
}