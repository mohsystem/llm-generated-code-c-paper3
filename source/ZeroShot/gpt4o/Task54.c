#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Method to generate a random OTP
void generate_otp(char* otp, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        otp[i] = '0' + (rand() % 10);
    }
    otp[length] = '\0';
}

// Simulated method to send OTP to user (here just prints to console)
void send_otp(const char* otp) {
    printf("OTP for login: %s\n", otp);
}

// Simulated method for 2FA process
int authenticate_user(const char* entered_otp, const char* generated_otp) {
    return strcmp(entered_otp, generated_otp) == 0;
}

int main() {
    srand((unsigned int)time(NULL));
    char otp[7]; // 6 digits + null terminator
    char entered_otp[7];

    // Test cases
    for (int i = 0; i < 5; ++i) {
        generate_otp(otp, 6);
        send_otp(otp);
        printf("Enter received OTP: ");
        scanf("%6s", entered_otp); // Limit input to 6 characters
        if (authenticate_user(entered_otp, otp)) {
            printf("Authentication Successful\n");
        } else {
            printf("Authentication Failed\n");
        }
    }
    return 0;
}