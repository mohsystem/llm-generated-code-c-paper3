#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    return (xor == 0 || numsSize % 2 == 0);
}

int main() {
    int arr1[] = {1,1,2};
    int arr2[] = {0,1};
    int arr3[] = {1,2,3};
    printf("%d\n", xorGame(arr1, 3)); // 0 (false)
    printf("%d\n", xorGame(arr2, 2)); // 1 (true)
    printf("%d\n", xorGame(arr3, 3)); // 1 (true)
    return 0;
}