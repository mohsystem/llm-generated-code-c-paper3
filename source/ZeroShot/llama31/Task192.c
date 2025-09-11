#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int len) {
    int xor = 0;
    for (int i = 0; i < len; ++i) {
        xor ^= nums[i];
    }
    return xor == 0 || len % 2 == 0;
}

int main() {
    int testCases[][3] = {
        {1, 1, 2},
        {0, 1},
        {1, 2, 3}
    };
    int lengths[] = {3, 2, 3};
    for (int i = 0; i < 3; ++i) {
        printf("%d\n", xorGame(testCases[i], lengths[i]));
    }
    return 0;
}