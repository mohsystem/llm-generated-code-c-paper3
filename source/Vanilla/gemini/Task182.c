#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* cleanPhoneNumber(const char* phoneNumber) {
    char* cleanedNumber = (char*)malloc(strlen(phoneNumber) + 1);
    int j = 0;
    for (int i = 0; phoneNumber[i] != '\0'; i++) {
        if (isdigit(phoneNumber[i])) {
            cleanedNumber[j++] = phoneNumber[i];
        }
    }
    cleanedNumber[j] = '\0';

    if (strlen(cleanedNumber) > 0 && cleanedNumber[0] == '1' && strlen(cleanedNumber) == 11) {
        char *result = (char*)malloc(11);
        strcpy(result, cleanedNumber + 1);
        free(cleanedNumber);
        return result;

    }
    if (strlen(cleanedNumber) == 10) {
        return cleanedNumber;
    }
     free(cleanedNumber);
    return ""; //  return NULL or empty string
}

int main() {
    const char* testCases[] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "1234567890123"
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < numTestCases; i++) {
        char *result = cleanPhoneNumber(testCases[i]);
        printf("%s\n", result);
        if (result && strlen(result)>0) free(result);
    }
    return 0;
}