#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanPhoneNumber(char* phoneNumber) {
    char cleaned[11];
    int j = 0;
    for (int i = 0; i < strlen(phoneNumber); i++) {
        if (isdigit(phoneNumber[i])) {
            cleaned[j++] = phoneNumber[i];
        }
    }
    cleaned[j] = '\0';
    if (j > 10) {
        strcpy(cleaned, cleaned + j - 10);
    }
    strcpy(phoneNumber, cleaned);
}

int main() {
    char testCases[][20] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "(613) 995-0253"
    };

    for (int i = 0; i < 5; i++) {
        cleanPhoneNumber(testCases[i]);
        printf("%s\n", testCases[i]);
    }

    return 0;
}