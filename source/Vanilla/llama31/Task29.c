#include <stdio.h>

void twoSum(int* nums, int n, int target, int* result) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return;
            }
        }
    }
}

int main() {
    int testCases[][5] = {
        {1, 2, 3},
        {3, 2, 4},
        {2, 7, 11, 15},
        {3, 3},
        {5, 7, 11}
    };
    int targets[] = {4, 6, 9, 6, 12};
    int lengths[] = {3, 3, 4, 2, 3};

    for (int i = 0; i < 5; i++) {
        int result[2];
        twoSum(testCases[i], lengths[i], targets[i], result);
        printf("Indices for target %d: (%d, %d)\n", targets[i], result[0], result[1]);
    }

    return 0;
}