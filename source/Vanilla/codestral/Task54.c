#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateOTP() {
    srand(time(0));
    return 100000 + rand() % 900000;
}

int verifyOTP(int userInput, int otp) {
    return userInput == otp;
}

int main() {
    int otp = generateOTP();
    printf("Generated OTP: %d\n", otp);

    // For testing purposes, we'll assume the user inputs the OTP correctly
    int userInput = otp;
    if (verifyOTP(userInput, otp)) {
        printf("Login successful\n");
    } else {
        printf("Invalid OTP\n");
    }

    return 0;
}