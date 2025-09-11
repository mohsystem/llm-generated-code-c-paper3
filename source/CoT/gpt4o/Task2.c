#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValidPhoneNumber(int* numbers, size_t size) {
    if (size != 10) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            return false;
        }
    }
    return true;
}

char* createPhoneNumber(int* numbers, size_t size) {
    if (!isValidPhoneNumber(numbers, size)) {
        return NULL;
    }
    char* phoneNumber = (char*)malloc(15 * sizeof(char));
    if (!phoneNumber) {
        return NULL; // Allocation failed
    }
    sprintf(phoneNumber, "(%d%d%d) %d%d%d-%d%d%d%d", 
            numbers[0], numbers[1], numbers[2], 
            numbers[3], numbers[4], numbers[5], 
            numbers[6], numbers[7], numbers[8], numbers[9]);
    return phoneNumber;
}

int main() {
    int test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int test2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int test3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test4[] = {3, 3, 3, 4, 4, 4, 5, 5, 5, 5};
    int test5[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    char* phone1 = createPhoneNumber(test1, 10);
    char* phone2 = createPhoneNumber(test2, 10);
    char* phone3 = createPhoneNumber(test3, 10);
    char* phone4 = createPhoneNumber(test4, 10);
    char* phone5 = createPhoneNumber(test5, 10);

    if (phone1) {
        printf("%s\n", phone1);
        free(phone1);
    }
    if (phone2) {
        printf("%s\n", phone2);
        free(phone2);
    }
    if (phone3) {
        printf("%s\n", phone3);
        free(phone3);
    }
    if (phone4) {
        printf("%s\n", phone4);
        free(phone4);
    }
    if (phone5) {
        printf("%s\n", phone5);
        free(phone5);
    }

    return 0;
}