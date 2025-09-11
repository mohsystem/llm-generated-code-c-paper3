#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* accum(const char* str, char* result) {
    int len = strlen(str);
    int resultIndex = 0;
    for (int i = 0; i < len; ++i) {
        char c = str[i];
        for (int j = 0; j <= i; ++j) {
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
    result[resultIndex] = '\0';
    return result;
}

int main() {
    char result[1024];
    printf("%s\n", accum("abcd", result)); // "A-Bb-Ccc-Dddd"
    printf("%s\n", accum("RqaEzty", result)); // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    printf("%s\n", accum("cwAt", result)); // "C-Ww-Aaa-Tttt"
    printf("%s\n", accum("", result)); // ""
    printf("%s\n", accum("a", result)); // "A"
    return 0;
}