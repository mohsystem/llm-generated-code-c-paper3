#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int isValidNANP(const char* number) {
    return strlen(number) == 10 && number[0] >= '2' && number[0] <= '9' &&
           number[3] >= '2' && number[3] <= '9';
}

char* cleanNumber(const char* input) {
    char cleaned[12] = "";
    int j = 0;
    
    // Remove all non-digit characters
    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) {
            cleaned[j++] = input[i];
        }
    }
    cleaned[j] = '\0';

    // Remove leading '1' if present
    if (strlen(cleaned) == 11 && cleaned[0] == '1') {
        memmove(cleaned, cleaned + 1, strlen(cleaned));
    }

    // Validate the cleaned number
    if (!isValidNANP(cleaned)) {
        fprintf(stderr, "Invalid NANP phone number\n");
        exit(1);
    }

    return strdup(cleaned);
}

int main() {
    // Test cases
    printf("%s\n", cleanNumber("+1 (613)-995-0253")); // Output: 6139950253
    printf("%s\n", cleanNumber("613-995-0253"));      // Output: 6139950253
    printf("%s\n", cleanNumber("1 613 995 0253"));    // Output: 6139950253
    printf("%s\n", cleanNumber("613.995.0253"));      // Output: 6139950253
    printf("%s\n", cleanNumber("1-800-555-0123"));    // Output: 8005550123

    return 0;
}