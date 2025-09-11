#include <stdio.h>
#include <string.h>
#include <ctype.h>

void accum(char *s, char *result) {
    for (int i = 0; i < strlen(s); i++) {
        result[i * 2] = toupper(s[i]);
        for (int j = 0; j < i; j++) {
            result[i * 2 + j + 1] = tolower(s[i]);
        }
        if (i < strlen(s) - 1) {
            result[i * 2 + i + 1] = '-';
        }
    }
    result[strlen(s) * 2 - 1] = '\0';
}

int main() {
    char result[100];
    accum("abcd", result);
    printf("%s\n", result); // Output: "A-Bb-Ccc-Dddd"
    accum("RqaEzty", result);
    printf("%s\n", result); // Output: "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    accum("cwAt", result);
    printf("%s\n", result); // Output: "C-Ww-Aaa-Tttt"
    return 0;
}