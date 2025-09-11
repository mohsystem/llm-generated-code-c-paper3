#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generate_otp() {
    srand(time(0));
    int number = 100000 + rand() % 900000;
    char* otp = malloc(sizeof(char) * 7);
    snprintf(otp, 7, "%d", number);
    return otp;
}

int validate_otp(const char* input_otp, const char* expected_otp) {
    return strcmp(input_otp, expected_otp) == 0;
}

int main() {
    char* expected_otp = generate_otp();
    printf("Generated OTP: %s\n", expected_otp);

    // Test cases
    const char* test_cases[] = {"123456", "654321", expected_otp, "987654", "456789"};
    for (int i = 0; i < 5; i++) {
        printf("Input OTP: %s, Valid: %s\n", test_cases[i], validate_otp(test_cases[i], expected_otp) ? "true" : "false");
    }

    free(expected_otp);
    return 0;
}