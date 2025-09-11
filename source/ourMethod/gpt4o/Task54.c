#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateOTP(char *otp, int length) {
    char numbers[] = "0123456789";
    srand(time(0));

    for (int i = 0; i < length; i++) {
        otp[i] = numbers[rand() % strlen(numbers)];
    }
    otp[length] = '\0';
}

int verifyOTP(const char *userInput, const char *generatedOTP) {
    return strcmp(userInput, generatedOTP) == 0;
}

int main() {
    // Test cases
    char otp1[7];
    generateOTP(otp1, 6);
    printf("Generated OTP: %s\n", otp1);
    printf("Verification: %d\n", verifyOTP(otp1, otp1)); // Should return 1

    char otp2[7];
    generateOTP(otp2, 6);
    printf("Generated OTP: %s\n", otp2);
    printf("Verification: %d\n", verifyOTP("123456", otp2)); // Should return 0

    char otp3[7];
    generateOTP(otp3, 6);
    printf("Generated OTP: %s\n", otp3);
    printf("Verification: %d\n", verifyOTP(otp3, otp3)); // Should return 1

    char otp4[7];
    generateOTP(otp4, 6);
    printf("Generated OTP: %s\n", otp4);
    printf("Verification: %d\n", verifyOTP("000000", otp4)); // Should return 0

    char otp5[7];
    generateOTP(otp5, 6);
    printf("Generated OTP: %s\n", otp5);
    printf("Verification: %d\n", verifyOTP(otp5, otp5)); // Should return 1

    return 0;
}