#include <stdio.h>

char* createPhoneNumber(int numbers[10], char* result) {
    sprintf(result, "(%d%d%d) %d%d%d-%d%d%d%d", 
            numbers[0], numbers[1], numbers[2], 
            numbers[3], numbers[4], numbers[5], 
            numbers[6], numbers[7], numbers[8], numbers[9]);
    return result;
}

int main() {
    int testCases[][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 3, 2, 1, 0, 9, 8, 7, 6, 5},
        {5, 6, 7, 8, 9, 0, 1, 2, 3, 4}
    };

    char result[20];

    for (int i = 0; i < 5; ++i) {
        printf("%s\n", createPhoneNumber(testCases[i], result));
    }

    return 0;
}