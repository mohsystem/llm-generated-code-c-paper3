#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define OTP_LENGTH 6

char* generateOTP() {
    char* otp = (char*)malloc(sizeof(char) * (OTP_LENGTH + 1));
    srand(time(NULL));
    for (int i = 0; i < OTP_LENGTH; i++) {
        otp[i] = '0' + (rand() % 10);
    }
    otp[OTP_LENGTH] = '\0';
    return otp;
}


int verifyOTP(const char* userOTP, const char* generatedOTP) {

    usleep(50000); // Introduce a small delay

    return strcmp(userOTP, generatedOTP) == 0;

}

int main() {

    char *testUsernames[] = {"user1", "user2", "user3", "user4", "user5"};

    for (int i = 0; i < 5; i++) {
        char* otp = generateOTP();
        printf("%s: %s\n", testUsernames[i], otp); // Send OTP through secure channel

        char userEnteredOTP[OTP_LENGTH + 1];
        strcpy(userEnteredOTP, otp); //Simulate user entering OTP. Replace with actual user input in real application.

        if (verifyOTP(userEnteredOTP, otp)) {
            printf("%s: Login successful\n", testUsernames[i]);
        } else {
            printf("%s: Login failed\n", testUsernames[i]);
        }
        free(otp);
    }
    return 0;
}