#include <stdio.h>
#include <regex.h>

void cleanPhoneNumber(char *phoneNumber) {
    regex_t regex;
    regcomp(&regex, "\\D", REG_EXTENDED);
    regsub(&regex, phoneNumber, 0, "", 0);
    regfree(&regex);
}

int main() {
    char *testCases[] = {"+1 (613)-995-0253", "613-995-0253", "1 613 995 0253", "613.995.0253"};
    for (int i = 0; i < 4; i++) {
        cleanPhoneNumber(testCases[i]);
        printf("%s\n", testCases[i]);
    }
    return 0;
}