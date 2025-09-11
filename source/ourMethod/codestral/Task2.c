#include <stdio.h>
#include <stdlib.h>

char* createPhoneNumber(const int numbers[10]) {
    // Validating input range
    for (int i = 0; i < 10; i++) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            fprintf(stderr, "Input array elements must be between 0 and 9\n");
            exit(1);
        }
    }

    // Formatting phone number
    char* phoneNumber = malloc(14);
    snprintf(phoneNumber, 14, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    char* phoneNumber = createPhoneNumber(numbers);
    printf("%s\n", phoneNumber); // => returns "(123) 456-7890"
    free(phoneNumber);
    return 0;
}