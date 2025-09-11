#include <stdio.h>

void twoSum(int numbers[], int size, int target, int result[]) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (numbers[i] + numbers[j] == target) {
                result[0] = i;
                result[1] = j;
                return;
            }
        }
    }
}

int main() {
    int result[2];
    int numbers1[] = {1, 2, 3};
    twoSum(numbers1, 3, 4, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers2[] = {3, 2, 4};
    twoSum(numbers2, 3, 6, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers3[] = {2, 7, 11, 15};
    twoSum(numbers3, 4, 9, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers4[] = {3, 3};
    twoSum(numbers4, 2, 6, result);
    printf("[%d, %d]\n", result[0], result[1]);

    int numbers5[] = {1, 4, 5, 3, 2};
    twoSum(numbers5, 5, 8, result);
    printf("[%d, %d]\n", result[0], result[1]);

    return 0;
}