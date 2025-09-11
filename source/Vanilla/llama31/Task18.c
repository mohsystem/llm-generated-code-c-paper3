#include <stdio.h>

int binaryArrayToInt(int* binaryArray, int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = (result << 1) | binaryArray[i];
    }
    return result;
}

void printArray(int* array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", array[i]);
    }
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
        printArray(testCases[i], lengths[i]);
        printf(" ==> %d\n", binaryArrayToInt(testCases[i], lengths[i]));
    }

    return 0;
}