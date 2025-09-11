#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_otp(char *otp, int length) {
    char numbers[] = "0123456789";
    for (int i = 0; i < length; ++i) {
        int index = rand() % 10;
        otp[i] = numbers[index];
    }
    otp[length] = '\0'; // Null-terminate the string
}

int main() {
    srand(time(0)); // Seed for random number generation
    char otp[7];
    
    // Test cases
    for (int i = 0; i < 5; ++i) {
        generate_otp(otp, 6);
        printf("Test Case %d: OTP is %s\n", i + 1, otp);
    }

    return 0;
}