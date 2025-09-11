#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generateOTP() {
    static char otp[7];
    srand(time(0));
    sprintf(otp, "%06d", 100000 + rand() % 900000);
    return otp;
}

int main() {
    // 5 test cases for generating OTP
    for (int i = 0; i < 5; ++i) {
        printf("Generated OTP: %s\n", generateOTP());
    }
    return 0;
}