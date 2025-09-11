#include <stdio.h>
#include <string.h>

void cleanPhoneNumber(char* phoneNumber) {
    char* ptr = phoneNumber;
    while (*ptr) {
        if (*ptr == '+' && ptr == phoneNumber) {
            ++ptr;
        } else if (*ptr == '1' && (ptr == phoneNumber || *(ptr - 1) == '+')) {
            ++ptr;
        } else if (isdigit(*ptr)) {
            *phoneNumber++ = *ptr++;
        } else {
            ++ptr;
        }
    }
    *phoneNumber = '\0';
}

int main() {
    char testCases[][20] = {
        "+1 (613)-995-0253",
        "613-995-0253",
        "1 613 995 0253",
        "613.995.0253",
        "+16139950253"
    };

    for (int i = 0; i < 5; ++i) {
        char phoneNumber[20];
        strcpy(phoneNumber, testCases[i]);
        cleanPhoneNumber(phoneNumber);
        printf("%s\n", phoneNumber);
    }

    return 0;
}