#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanPhoneNumber(const char* input, char* output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) {
            output[j++] = input[i]; // Collect all numeric characters
        }
    }
    output[j] = '\0';

    if (j == 11 && output[0] == '1') {
        // Remove the country code
        for (int i = 0; i < j - 1; i++) {
            output[i] = output[i + 1];
        }
        output[j - 1] = '\0';
    }
}

void runTestCases() {
    char output[12]; // Max length of a cleaned number + 1 for null-terminator
    cleanPhoneNumber("+1 (613)-995-0253", output);
    printf("%s\n", output); // 6139950253
    cleanPhoneNumber("613-995-0253", output);
    printf("%s\n", output); // 6139950253
    cleanPhoneNumber("1 613 995 0253", output);
    printf("%s\n", output); // 6139950253
    cleanPhoneNumber("613.995.0253", output);
    printf("%s\n", output); // 6139950253
    cleanPhoneNumber("1234567890", output);
    printf("%s\n", output); // 234567890
}

int main() {
    runTestCases();
    return 0;
}