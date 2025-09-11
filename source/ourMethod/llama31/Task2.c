#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createPhoneNumber(int numbers[]) {
    if (numbers == NULL) {
        fprintf(stderr, "Array must not be null\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; ++i) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            fprintf(stderr, "All elements must be between 0 and 9\n");
            exit(EXIT_FAILURE);
        }
    }

    char* phoneNumber = malloc(15 * sizeof(char));
    if (phoneNumber == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2],
            numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    char* phoneNumber = createPhoneNumber(numbers);
    printf("%s\n", phoneNumber);
    free(phoneNumber);
    return 0;
}