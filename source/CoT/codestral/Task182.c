#include <stdio.h>
#include <ctype.h>
#include <string.h>

void cleanPhoneNumber(char *phoneNumber) {
    int i, j = 0;
    for (i = 0; i < strlen(phoneNumber); ++i)
        if (isdigit(phoneNumber[i]))
            phoneNumber[j++] = phoneNumber[i];
    phoneNumber[j] = '\0';
}

int main() {
    char phoneNumber[15];
    strcpy(phoneNumber, "+1 (613)-995-0253");
    cleanPhoneNumber(phoneNumber);
    printf("%s\n", phoneNumber); // 6139950253

    strcpy(phoneNumber, "613-995-0253");
    cleanPhoneNumber(phoneNumber);
    printf("%s\n", phoneNumber); // 6139950253

    strcpy(phoneNumber, "1 613 995 0253");
    cleanPhoneNumber(phoneNumber);
    printf("%s\n", phoneNumber); // 6139950253

    strcpy(phoneNumber, "613.995.0253");
    cleanPhoneNumber(phoneNumber);
    printf("%s\n", phoneNumber); // 6139950253

    return 0;
}