#include <stdio.h>
#include <stdlib.h>

char* createPhoneNumber(int numbers[]) {
    char* phoneNumber = (char*) malloc(15 * sizeof(char));
    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", 
            numbers[0], numbers[1], numbers[2], 
            numbers[3], numbers[4], numbers[5], 
            numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int testCases[][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
        {4, 3, 2, 1, 0, 9, 8, 7, 6, 5},
        {5, 1, 9, 5, 5, 5, 4, 4, 6, 8},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    };

    for (int i = 0; i < 5; ++i) {
        char* phoneNumber = createPhoneNumber(testCases[i]);
        printf("%s\n", phoneNumber);
        free(phoneNumber);
    }

    return 0;
}