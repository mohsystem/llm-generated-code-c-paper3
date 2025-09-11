#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int size) {
    int xor = 0;
    for (int i = 0; i < size; ++i) {
        xor ^= nums[i];
    }
    return xor == 0 || size % 2 == 0;
}

int main() {
    int testCases[][4] = {
        {1, 1, 2, 0},
        {0, 1, 0, 0},
        {1, 2, 3, 0},
        {1, 2, 3, 4},
        {1, 1, 1, 1}
    };
    int testCaseSizes[] = {3, 2, 3, 4, 4};
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", xorGame(testCases[i], testCaseSizes[i]));
    }
    return 0;
}