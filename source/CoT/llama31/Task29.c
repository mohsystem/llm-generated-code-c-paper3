// C
#include <stdio.h>

void twoSum(int numbers[], int length, int target, int* result) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (numbers[i] + numbers[j] == target) {
                result[0] = i;
                result[1] = j;
                return;
            }
        }
    }
}

int main() {
    int numbers1[] = {1, 2, 3};
    int result1[2];
    twoSum(numbers1, 3, 4, result1);
    printf("(%d, %d)\n", result1[0], result1[1]);

    int numbers2[] = {3, 2, 4};
    int result2[2];
    twoSum(numbers2, 3, 6, result2);
    printf("(%d, %d)\n", result2[0], result2[1]);

    int numbers3[] = {10, 20, 30, 40};
    int result3[2];
    twoSum(numbers3, 4, 50, result3);
    printf("(%d, %d)\n", result3[0], result3[1]);

    int numbers4[] = {5, 10, 15, 20};
    int result4[2];
    twoSum(numbers4, 4, 25, result4);
    printf("(%d, %d)\n", result4[0], result4[1]);

    int numbers5[] = {2, 4, 6, 8};
    int result5[2];
    twoSum(numbers5, 4, 10, result5);
    printf("(%d, %d)\n", result5[0], result5[1]);

    return 0;
}