#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* cleanPhoneNumber(const char* phoneNumber) {
    char* cleanedNumber = malloc(strlen(phoneNumber) + 1);
    int j = 0;
    for (int i = 0; phoneNumber[i] != '\0'; i++) {
        if (isdigit(phoneNumber[i])) {
            cleanedNumber[j++] = phoneNumber[i];
        }
    }
    cleanedNumber[j] = '\0';

    if (strlen(cleanedNumber) > 10 && cleanedNumber[0] == '1') {
        memmove(cleanedNumber, cleanedNumber + 1, strlen(cleanedNumber));
    }
     if (strlen(cleanedNumber) != 10) {
        free(cleanedNumber);
        return NULL;
    }

    return cleanedNumber;
}

int main() {
    const char* testCases[] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "1234567890",
         "12345678"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char* cleanedNumber = cleanPhoneNumber(testCases[i]);
        if (cleanedNumber != NULL) {
            printf("%s\n", cleanedNumber);
            free(cleanedNumber);
        } else {
             printf("%s\n", "");
        }
    }

    return 0;
}