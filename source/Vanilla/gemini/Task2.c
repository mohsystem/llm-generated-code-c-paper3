#include <stdio.h>
#include <string.h>

char* createPhoneNumber(int numbers[10]) {
    static char phoneNumber[15]; //  Static to persist after function returns
    if (sizeof(numbers) != sizeof(int[10])){
         strcpy(phoneNumber, "Invalid input array length. Must be 10.");
         return phoneNumber;
    }
    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int test2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int test3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int test4[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    printf("%s\n", createPhoneNumber(test1));
    printf("%s\n", createPhoneNumber(test2));
    printf("%s\n", createPhoneNumber(test3));
    printf("%s\n", createPhoneNumber(test4));
    printf("%s\n", createPhoneNumber(test5));

    return 0;
}