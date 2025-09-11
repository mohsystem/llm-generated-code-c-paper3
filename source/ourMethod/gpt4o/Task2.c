#include <stdio.h>
#include <stdlib.h>

void createPhoneNumber(int numbers[], char* result) {
    for (int i = 0; i < 10; ++i) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            fprintf(stderr, "All numbers must be between 0 and 9.\n");
            exit(EXIT_FAILURE);
        }
    }
    sprintf(result, "(%d%d%d) %d%d%d-%d%d%d%d", 
            numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], 
            numbers[6], numbers[7], numbers[8], numbers[9]);
}

int main() {
    int testCases[5][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
        {0, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {9, 0, 1, 2, 3, 4, 5, 6, 7, 8},
        {2, 3, 4, 5, 6, 7, 8, 9, 0, 1}
    };

    char result[15];

    for (int i = 0; i < 5; ++i) {
        createPhoneNumber(testCases[i], result);
        printf("%s\n", result);
    }

    return 0;
}