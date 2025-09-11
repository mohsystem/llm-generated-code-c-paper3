#include <stdio.h>

void createPhoneNumber(int numbers[], char *phoneNumber) {
    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
}

int main() {
    int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    char phoneNumber[15];
    createPhoneNumber(numbers, phoneNumber);
    printf("%s\n", phoneNumber); // "(123) 456-7890"

    int numbers2[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    createPhoneNumber(numbers2, phoneNumber);
    printf("%s\n", phoneNumber); // "(987) 654-3210"

    int numbers3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    createPhoneNumber(numbers3, phoneNumber);
    printf("%s\n", phoneNumber); // "(012) 345-6789"

    int numbers4[10] = {5, 5, 5, 1, 2, 3, 4, 5, 6, 7};
    createPhoneNumber(numbers4, phoneNumber);
    printf("%s\n", phoneNumber); // "(555) 123-4567"

    int numbers5[10] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    createPhoneNumber(numbers5, phoneNumber);
    printf("%s\n", phoneNumber); // "(999) 999-9999"

    return 0;
}