#include <stdio.h>
#include <ctype.h>
#include <string.h>

void cleanPhoneNumber(char* number) {
    int i, j = 0;
    for (i = 0; i < strlen(number); i++) {
        if (isdigit(number[i])) {
            number[j++] = number[i];
        }
    }
    number[j] = 0;
}

int main() {
    char number[20];
    strcpy(number, "+1 (613)-995-0253");
    cleanPhoneNumber(number);
    printf("%s\n", number); // 6139950253
    strcpy(number, "613-995-0253");
    cleanPhoneNumber(number);
    printf("%s\n", number); // 6139950253
    strcpy(number, "1 613 995 0253");
    cleanPhoneNumber(number);
    printf("%s\n", number); // 6139950253
    strcpy(number, "613.995.0253");
    cleanPhoneNumber(number);
    printf("%s\n", number); // 6139950253
    return 0;
}