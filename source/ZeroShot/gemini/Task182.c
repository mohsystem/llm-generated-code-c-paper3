#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* cleanPhoneNumber(const char* phoneNumber) {
    char* cleanedNumber = (char*)malloc(strlen(phoneNumber) + 1); // Allocate enough memory
    if (cleanedNumber == NULL) return NULL; // Handle memory allocation failure
    int j = 0;
    for (int i = 0; phoneNumber[i] != '\0'; i++) {
        if (isdigit(phoneNumber[i])) {
            cleanedNumber[j++] = phoneNumber[i];
        }
    }
    cleanedNumber[j] = '\0';

    if (strlen(cleanedNumber) == 11 && cleanedNumber[0] == '1') {
        char *result = (char *)malloc(11); // Allocate for 10 digits + null terminator
        if (result == NULL) {
            free(cleanedNumber); // Free the original cleaned number
            return NULL; // Return NULL to indicate error
        }
        strcpy(result, cleanedNumber + 1);
        free(cleanedNumber); // Free the original cleaned number
        return result;
    }
    if (strlen(cleanedNumber) == 10) {
        return cleanedNumber;
    }
    free(cleanedNumber); // Free allocated memory if not a valid number
    return NULL; // Or return an empty string
}

int main() {
    const char* testCases[] = {"+1 (613)-995-0253", "613-995-0253", "1 613 995 0253", "613.995.0253", "1234567890123"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < numTestCases; i++) {
        char *cleaned = cleanPhoneNumber(testCases[i]);
        if (cleaned != NULL) {
            printf("%s\n", cleaned);
            free(cleaned); // Free the allocated memory
        } else {
             printf("(null)\n"); // Indicate an invalid number
        }
    }
    return 0;
}