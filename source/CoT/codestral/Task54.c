#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PASSWORD_LENGTH 6

char* generateOTP() {
    srand(time(0));
    int number = 100000 + rand() % 900000;
    char* otp = (char*)malloc(sizeof(char) * (PASSWORD_LENGTH + 1));
    sprintf(otp, "%d", number);
    return otp;
}

int validateOTP(const char* userInput, const char* generatedOTP) {
    return strcmp(userInput, generatedOTP) == 0;
}

int main() {
    char* otp = generateOTP();
    printf("Generated OTP: %s\n", otp);

    // Test cases
    printf("%d\n", validateOTP("123456", otp));
    printf("%d\n", validateOTP("654321", otp));
    printf("%d\n", validateOTP("999999", otp));
    printf("%d\n", validateOTP(otp, otp));

    free(otp);
    return 0;
}