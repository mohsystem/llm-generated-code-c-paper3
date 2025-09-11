#include <stdio.h>
#include <stdlib.h>

void createPhoneNumber(int numbers[], char *phoneNumber) {
    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    char phoneNumber[15];
    createPhoneNumber(numbers, phoneNumber);
    printf("%s\n", phoneNumber);
    return 0;
}