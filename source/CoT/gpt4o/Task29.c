#include <stdio.h>

void twoSum(const int* numbers, int size, int target, int* result) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (numbers[i] + numbers[j] == target) {
                result[0] = i;
                result[1] = j;
                return;
            }
        }
    }
    result[0] = -1; // Return -1, -1 if no solution is found (shouldn't happen given problem statement)
    result[1] = -1;
}

int main() {
    int result[2];

    twoSum((int[]){1, 2, 3}, 3, 4, result);
    printf("{%d, %d}\n", result[0], result[1]);

    twoSum((int[]){3, 2, 4}, 3, 6, result);
    printf("{%d, %d}\n", result[0], result[1]);

    twoSum((int[]){2, 7, 11, 15}, 4, 9, result);
    printf("{%d, %d}\n", result[0], result[1]);

    twoSum((int[]){5, 75, 25}, 3, 100, result);
    printf("{%d, %d}\n", result[0], result[1]);

    twoSum((int[]){1, 3, 4, 2}, 4, 6, result);
    printf("{%d, %d}\n", result[0], result[1]);

    return 0;
}