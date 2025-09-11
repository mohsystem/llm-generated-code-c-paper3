// C code
#include <stdio.h>

void twoSum(int* numbers, int length, int target, int* result) {
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
    int testCases[][5] = {
        {1, 2, 3},
        {3, 2, 4},
        {10, 20, 30, 40},
        {5, 10, 15, 20},
        {1, 3, 5, 7}
    };
    int targets[] = {4, 6, 50, 30, 8};
    int lengths[] = {3, 3, 4, 4, 4};

    for (int i = 0; i < 5; i++) {
        int result[2];
        twoSum(testCases[i], lengths[i], targets[i], result);
        printf("twoSum({");
        for (int j = 0; j < lengths[i]; j++) {
            printf("%d", testCases[i][j]);
            if (j < lengths[i] - 1) printf(", ");
        }
        printf("}, %d) == (%d, %d)\n", targets[i], result[0], result[1]);
    }

    return 0;
}