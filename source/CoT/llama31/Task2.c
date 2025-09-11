#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createPhoneNumber(int numbers[10]) {
    // Problem understanding: Convert array of integers into a phone number format
    // Security requirements: Ensure input array is of correct length and contains valid integers

    if (sizeof(numbers) / sizeof(numbers[0]) != 10) {
        fprintf(stderr, "Input array must be of length 10\n");
        exit(EXIT_FAILURE);
    }

    // Secure coding generation: Format the phone number step-by-step
    char* phoneNumber = malloc(15 * sizeof(char));
    if (!phoneNumber) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);

    return phoneNumber;
}

int main() {
    // Test cases
    int test1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int test2[10] = {5, 1, 9, 5, 5, 5, 4, 4, 6, 8};
    int test3[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int test4[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test5[10] = {4, 3, 2, 1, 0, 9, 8, 7, 6, 5};

    char* result1 = createPhoneNumber(test1);
    char* result2 = createPhoneNumber(test2);
    char* result3 = createPhoneNumber(test3);
    char* result4 = createPhoneNumber(test4);
    char* result5 = createPhoneNumber(test5);

    printf("%s\n", result1); // => returns "(123) 456-7890"
    printf("%s\n", result2); // => returns "(519) 555-4468"
    printf("%s\n", result3); // => returns "(000) 000-0000"
    printf("%s\n", result4); // => returns "(987) 654-3210"
    printf("%s\n", result5); // => returns "(432) 109-8765"

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}