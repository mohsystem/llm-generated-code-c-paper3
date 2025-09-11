#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int n) {
    int xor = 0;
    for (int i = 0; i < n; i++) {
        xor ^= nums[i];
    }
    if (xor == 0) {
        return true;
    }
    if (n % 2 == 0) {
        return true;
    }
    for (int i = 0; i < n; i++) {
        if ((xor ^ nums[i]) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int testCases[][4] = {
        {1, 1, 2, 0},
        {0, 1, 0, 0},
        {1, 2, 3, 0},
        {1, 2, 4, 0},
        {1, 1, 1, 1}
    };
    int lengths[] = {3, 2, 3, 3, 4};
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", xorGame(testCases[i], lengths[i]));
    }
    return 0;
}