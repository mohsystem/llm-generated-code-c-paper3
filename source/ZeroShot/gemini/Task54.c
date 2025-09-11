#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate OTP of specified length
char* generateOTP(int length) {
    char* numbers = "0123456789";
    char* otp = (char*)malloc(sizeof(char) * (length + 1)); 
    if (otp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // Or handle the error appropriately
    }


    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        otp[i] = numbers[rand() % 10];
    }
    otp[length] = '\0';
    return otp;
}

// Function to implement 2FA
int twoFactorAuth(const char* username, const char* password, int otpLength) {
    if (strcmp(username, "user") == 0 && strcmp(password, "password") == 0) {
        char* otp = generateOTP(otpLength);
        char enteredOTP[20]; // Adjust size as needed

        printf("Your OTP is: %s\n", otp);
        printf("Enter OTP: ");
        scanf("%s", enteredOTP);


        int result = strcmp(otp, enteredOTP) == 0;
        free(otp); // Free the dynamically allocated memory
        return result;
    }
    return 0; // Or return a specific value indicating failure.
}

int main() {
    // Test cases
    printf("%d\n", twoFactorAuth("user", "password", 6));
    printf("%d\n", twoFactorAuth("user", "wrongpassword", 6));
    printf("%d\n", twoFactorAuth("wronguser", "password", 6));
    printf("%d\n", twoFactorAuth("user", "password", 4));
    printf("%d\n", twoFactorAuth("user", "password", 8));

    return 0;
}