#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanPhoneNumber(const char *input, char *output) {
    int j = 0;
    int length = strlen(input);
    // Copy numeric characters
    for (int i = 0; i < length; i++) {
        if (isdigit(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0'; // Null-terminate the string

    // Remove the country code if present
    if (output[0] == '1' && strlen(output) == 11) {
        memmove(output, output + 1, strlen(output));
    }
}

int main() {
    char output[12];
    cleanPhoneNumber("+1 (613)-995-0253", output);
    printf("%s\n", output);  // 6139950253

    cleanPhoneNumber("613-995-0253", output);
    printf("%s\n", output);  // 6139950253

    cleanPhoneNumber("1 613 995 0253", output);
    printf("%s\n", output);  // 6139950253

    cleanPhoneNumber("613.995.0253", output);
    printf("%s\n", output);  // 6139950253

    cleanPhoneNumber("+1-800-555-0199", output);
    printf("%s\n", output);  // 8005550199

    return 0;
}