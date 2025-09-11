#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanPhoneNumber(char* phoneNumber) {
    char* ptr = phoneNumber;
    while (*ptr != '\0') {
        if (*ptr == '+' || *ptr == '1' && *(ptr + 1) == ' ') {
            // Skip country code
            ptr++;
            if (*ptr == ' ') ptr++;
        } else if (!isdigit(*ptr)) {
            // Skip non-digit characters
            memmove(ptr, ptr + 1, strlen(ptr));
        } else {
            ptr++;
        }
    }
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