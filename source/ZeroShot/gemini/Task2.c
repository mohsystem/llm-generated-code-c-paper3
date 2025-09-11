#include <stdio.h>
#include <string.h>

char* createPhoneNumber(int numbers[10]) {
    char* phoneNumber = (char*)malloc(sizeof(char) * 15);
    if (phoneNumber == NULL) {
        return NULL; // Handle memory allocation failure
    }
    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int testCases[5][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < 5; i++) {
        char* result = createPhoneNumber(testCases[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result); // Free allocated memory
        } else {
            printf("Memory allocation failed!\n");
        }
    }

    return 0;
}