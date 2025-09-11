#include <stdio.h>

void twoSum(int numbers[], int length, int target, int result[2]) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (numbers[i] + numbers[j] == target) {
                result[0] = i;
                result[1] = j;
                return;
            }
        }
    }
    result[0] = result[1] = -1; // No solution found
}

int main() {
    // Test cases
    int result[2];

    int numbers1[] = { 1, 2, 3 };
    twoSum(numbers1, 3, 4, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers2[] = { 3, 2, 4 };
    twoSum(numbers2, 3, 6, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers3[] = { 2, 7, 11, 15 };
    twoSum(numbers3, 4, 9, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers4[] = { 3, 3 };
    twoSum(numbers4, 2, 6, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers5[] = { 0, 4, 3, 0 };
    twoSum(numbers5, 4, 0, result);
    printf("[%d, %d]\n", result[0], result[1]);

    return 0;
}