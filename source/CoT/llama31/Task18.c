#include <stdio.h>

int binaryArrayToInt(int* binaryArray, int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

int main() {
    int testCases[][4] = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 0, 1, 1}
    };
    int lengths[] = {4, 4, 4, 4, 4, 4, 4, 4};

    for (int i = 0; i < 8; i++) {
        printf("Testing: ");
        for (int j = 0; j < lengths[i]; j++) {
            printf("%d", testCases[i][j]);
        }
        printf(" ==> %d\n", binaryArrayToInt(testCases[i], lengths[i]));
    }

    return 0;
}