#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanPhoneNumber(char *phoneNumber, char *cleanedNumber) {
    int j = 0;
    for (int i = 0; phoneNumber[i] != '\0'; i++) {
        if (isdigit(phoneNumber[i])) {
            cleanedNumber[j++] = phoneNumber[i];
        }
    }
    cleanedNumber[j] = '\0';

    if (strlen(cleanedNumber) == 11 && cleanedNumber[0] == '1') {
        memmove(cleanedNumber, cleanedNumber + 1, strlen(cleanedNumber));
    }
}


int main() {
    char testCases[][25] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "16139950253"
    };

    for (int i = 0; i < 5; i++) {
        char cleanedNumber[25];
        cleanPhoneNumber(testCases[i], cleanedNumber);
        printf("%s\n", cleanedNumber);
    }

    return 0;
}