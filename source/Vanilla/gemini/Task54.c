#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateOTP(int length) {
    char* numbers = "0123456789";
    char* otp = malloc(sizeof(char) * (length + 1));
    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        otp[i] = numbers[rand() % 10];
    }
    otp[length] = '\0';
    return otp;
}

int main() {
    char* otp1 = generateOTP(6);
    printf("%s\n", otp1);
    free(otp1);

    char* otp2 = generateOTP(8);
    printf("%s\n", otp2);
    free(otp2);

    char* otp3 = generateOTP(4);
    printf("%s\n", otp3);
    free(otp3);

    char* otp4 = generateOTP(6);
    printf("%s\n", otp4);
    free(otp4);

    char* otp5 = generateOTP(10);
    printf("%s\n", otp5);
    free(otp5);


    return 0;
}