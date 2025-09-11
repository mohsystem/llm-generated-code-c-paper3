#include <stdio.h>
#include <string.h>
#include <ctype.h>

void accum(char* str) {
    int len = strlen(str);
    char result[len * 2 + len + 1]; // max possible length
    int resultIndex = 0;

    for (int i = 0; i < len; i++) {
        char c = str[i];
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                result[resultIndex++] = toupper(c);
            } else {
                result[resultIndex++] = tolower(c);
            }
        }
        if (i < len - 1) {
            result[resultIndex++] = '-';
        }
    }
    result[resultIndex] = '\0'; // null terminate the string
    printf("%s\n", result);
}

int main() {
    char str1[] = "abcd";
    char str2[] = "RqaEzty";
    char str3[] = "cwAt";
    char str4[] = "";
    char str5[] = "a";

    accum(str1); // "A-Bb-Ccc-Dddd"
    accum(str2); // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    accum(str3); // "C-Ww-Aaa-Tttt"
    accum(str4); // ""
    accum(str5); // "A"

    return 0;
}