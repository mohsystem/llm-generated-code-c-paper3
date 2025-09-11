#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int n) {
    int xor = 0;
    for (int i = 0; i < n; ++i) {
        xor ^= nums[i];
    }
    if (xor == 0) {
        return true;
    }
    if (n % 2 == 0) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        if ((nums[i] ^ xor) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int testCases[][3] = {
        {1, 1, 2},
        {0, 1},
        {1, 2, 3}
    };
    int testCaseSizes[] = {3, 2, 3};
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", xorGame(testCases[i], testCaseSizes[i]) ? "true" : "false");
    }
    return 0;
}