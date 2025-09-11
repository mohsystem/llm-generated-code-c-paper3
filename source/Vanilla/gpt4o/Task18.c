#include <stdio.h>

int binaryArrayToInt(int binaryArray[], int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = result * 2 + binaryArray[i];
    }
    return result;
}

int main() {
    int testCases[5][4] = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}
    };
    
    for (int i = 0; i < 5; i++) {
        printf("%d\n", binaryArrayToInt(testCases[i], 4));
    }
    
    return 0;
}