#include <stdio.h>
#include <stdbool.h>

bool xorGame(int nums[], int numsSize) {
    int xor_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_sum ^= nums[i];
    }
    if (xor_sum == 0) {
        return true;
    }
    return numsSize % 2 == 0;
}

int main() {
    int testCases[][1000] = {
        {1, 1, 2},
        {0, 1},
        {1, 2, 3},
        {1, 1},
        {0}
    };
    int testCaseSizes[] = {3, 2, 3, 2, 1};
    bool expectedOutputs[] = {false, true, true, false, true};

    for (int i = 0; i < 5; i++) {
        bool actualOutput = xorGame(testCases[i], testCaseSizes[i]);
        printf("Test case %d: nums=", i + 1);
        for (int j = 0; j < testCaseSizes[i]; j++) {
            printf("%d%s", testCases[i][j], j == testCaseSizes[i] - 1 ? "" : ",");
        }
        printf(", Expected output: %s, Actual output: %s\n", expectedOutputs[i] ? "true" : "false", actualOutput ? "true" : "false");

        if (actualOutput != expectedOutputs[i]) {
            printf("Test case %d failed!\n", i + 1);
        }
    }

    return 0;
}