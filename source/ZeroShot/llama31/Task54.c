#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void mainFunction() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Test cases
    for (int i = 0; i < 5; i++) {
        char username[100], password[100];
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (authenticateUser(username, password)) {
            printf("Login successful\n");
        } else {
            printf("Login failed\n");
        }
    }
}

bool authenticateUser(const char* username, const char* password) {
    // Simulate database check (for simplicity, assume valid credentials)
    if (strcmp(username, "test") != 0 || strcmp(password, "test") != 0) {
        return false;
    }

    // Generate OTP
    char otp[7];
    sprintf(otp, "%06d", rand() % 900000 + 100000); // Generate 6-digit OTP
    printf("OTP sent to your device: %s\n", otp);

    // Prompt user to enter OTP
    char userOtp[7];
    printf("Enter OTP: ");
    scanf("%6s", userOtp);

    return strcmp(otp, userOtp) == 0;
}

int main() {
    mainFunction();
    return 0;
}