#include <stdio.h>
#include <ctype.h>
#include <string.h>

void cleanPhoneNumber(char *number) {
    int i, j = 0;
    for (i = 0; i < strlen(number); i++) {
        if (isdigit(number[i])) {
            number[j++] = number[i];
        }
    }
    number[j] = 0;
}

int main() {
    char *numbers[] = {"+1 (613)-995-0253", "613-995-0253", "1 613 995 0253", "613.995.0253"};
    for (int i = 0; i < 4; i++) {
        cleanPhoneNumber(numbers[i]);
        printf("%s\n", numbers[i]);
    }
    return 0;
}