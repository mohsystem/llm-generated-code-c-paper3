#include <stdio.h>
#include <stdbool.h>

bool xorGame(int nums[], int numsSize) {
    int xor_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_sum ^= nums[i];
    }
    return xor_sum == 0 || numsSize % 2 == 0;
}

int main() {
    int test1[] = {1, 1, 2};
    printf("%s\n", xorGame(test1, 3) ? "true" : "false"); // Output: false

    int test2[] = {0, 1};
    printf("%s\n", xorGame(test2, 2) ? "true" : "false"); // Output: true

    int test3[] = {1, 2, 3};
    printf("%s\n", xorGame(test3, 3) ? "true" : "false"); // Output: true

    int test4[] = {1, 1};
    printf("%s\n", xorGame(test4, 2) ? "true" : "false"); // Output: true

    int test5[] = {0};
    printf("%s\n", xorGame(test5, 1) ? "true" : "false"); // Output: true


    return 0;
}