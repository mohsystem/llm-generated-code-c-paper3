#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createPhoneNumber(int numbers[], int length) {
    if (length != 10) {
        fprintf(stderr, "Array must contain exactly 10 integers.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            fprintf(stderr, "Each integer must be between 0 and 9.\n");
            exit(EXIT_FAILURE);
        }
    }
    char *result = (char *)malloc(15 * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    snprintf(result, 15, "(%d%d%d) %d%d%d-%d%d%d%d",
             numbers[0], numbers[1], numbers[2], numbers[3],
             numbers[4], numbers[5], numbers[6], numbers[7],
             numbers[8], numbers[9]);
    return result;
}

int main() {
    char *phoneNumber;
    phoneNumber = createPhoneNumber((int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, 10);
    printf("%s\n", phoneNumber);
    free(phoneNumber);

    phoneNumber = createPhoneNumber((int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10);
    printf("%s\n", phoneNumber);
    free(phoneNumber);

    phoneNumber = createPhoneNumber((int[]){9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 10);
    printf("%s\n", phoneNumber);
    free(phoneNumber);

    phoneNumber = createPhoneNumber((int[]){3, 3, 3, 4, 4, 4, 5, 5, 5, 5}, 10);
    printf("%s\n", phoneNumber);
    free(phoneNumber);

    phoneNumber = createPhoneNumber((int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 10);
    printf("%s\n", phoneNumber);
    free(phoneNumber);

    return 0;
}