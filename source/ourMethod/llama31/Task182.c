#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanPhoneNumber(char* phoneNumber) {
    int len = strlen(phoneNumber);
    int j = 0;

    // Remove country code and punctuation
    for (int i = 0; i < len; i++) {
        if (phoneNumber[i] == '+' || phoneNumber[i] == '1' && (i == 0 || phoneNumber[i - 1] == ' ')) {
            continue;
        }
        if (!isdigit(phoneNumber[i])) {
            continue;
        }
        phoneNumber[j++] = phoneNumber[i];
    }
    phoneNumber[j] = '\0';
}

int main() {
    char testCases[][20] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253"
    };
    for (int i = 0; i < 4; i++) {
        cleanPhoneNumber(testCases[i]);
        printf("%s\n", testCases[i]);
    }
    return 0;
}