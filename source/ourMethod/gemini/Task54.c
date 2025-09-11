#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random OTP of specified length
char* generateOTP(int length) {
    char* otp = malloc(sizeof(char) * (length + 1));
    if (otp == NULL) {
        return NULL;
    }
    const char numbers[] = "0123456789";
    for (int i = 0; i < length; i++) {
        otp[i] = numbers[rand() % 10];
    }
    otp[length] = '\0';
    return otp;
}

// Function to implement two-factor authentication
int twoFactorAuthentication(const char* username, const char* password, int otpLength) {

    char enteredUsername[256];
    char enteredPassword[256];
    char enteredOTP[256];
    printf("Enter username:\n");
    scanf("%s", enteredUsername);

    printf("Enter password:\n");
    scanf("%s", enteredPassword);

    if (strcmp(username, enteredUsername) == 0 && strcmp(password, enteredPassword) == 0) {
        char* otp = generateOTP(otpLength);
        if (otp == NULL) {
            return 0; 
        }
        printf("Generated OTP: %s\n", otp);

        printf("Enter OTP:\n");
        scanf("%s", enteredOTP);
        int result = strcmp(otp, enteredOTP) == 0;
        free(otp);
        return result;
    } else {
        return 0;
    }
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Test cases
    printf("%d\n", twoFactorAuthentication("user1", "password123", 6));
    printf("%d\n", twoFactorAuthentication("user2", "securepass", 4));
    printf("%d\n", twoFactorAuthentication("user3", "mypassword", 8));
    printf("%d\n", twoFactorAuthentication("user1", "wrongpassword", 6));
    printf("%d\n", twoFactorAuthentication("wronguser", "password123", 6));

    return 0;
}