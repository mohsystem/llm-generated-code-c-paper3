#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool authenticate(const char* username, const char* password) {
    // In a real scenario, this would involve checking against a database
    return strcmp(username, "user") == 0 && strcmp(password, "password") == 0;
}

char* generateOtp() {
    srand(time(NULL));
    int otp = rand() % 900000 + 100000; // Generate a 6-digit OTP
    char* otpStr = malloc(7 * sizeof(char));
    sprintf(otpStr, "%06d", otp); // Ensure the OTP is always 6 digits
    return otpStr;
}

bool verifyOtp(const char* generatedOtp, const char* userOtp) {
    return strcmp(generatedOtp, userOtp) == 0;
}

int main() {
    char username[100], password[100];
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticate(username, password)) {
        char* otp = generateOtp();
        printf("Your OTP is: %s\n", otp);
        char userOtp[7];
        printf("Enter the OTP: ");
        fgets(userOtp, sizeof(userOtp), stdin);
        userOtp[strcspn(userOtp, "\n")] = 0; // Remove newline character

        if (verifyOtp(otp, userOtp)) {
            printf("Login successful!\n");
        } else {
            printf("Invalid OTP. Login failed.\n");
        }
        free(otp);
    } else {
        printf("Invalid username or password. Login failed.\n");
    }

    return 0;
}