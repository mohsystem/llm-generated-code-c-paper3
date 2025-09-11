#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void testCases() {
    for (int i = 0; i < 5; i++) {
        char username[100], password[100];
        printf("Enter username and password (separated by space): ");
        scanf("%s %s", username, password);
        if (authenticate(username, password)) {
            printf("Login successful!\n");
        } else {
            printf("Login failed!\n");
        }
    }
}

int authenticate(const char* username, const char* password) {
    // Simulate database check (for simplicity, assume credentials are valid)
    if (strcmp(username, "user") == 0 && strcmp(password, "password") == 0) {
        int otp = generateOtp();
        printf("Enter the OTP sent to your phone: %06d\n", otp);
        int userOtp;
        scanf("%d", &userOtp);
        return otp == userOtp;
    }
    return 0;
}

int generateOtp() {
    srand(time(NULL));
    return rand() % 900000 + 100000; // Generate 6-digit OTP
}

int main() {
    testCases();
    return 0;
}