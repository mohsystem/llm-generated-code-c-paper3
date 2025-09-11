#include <stdio.h>
#include <ctype.h>
#include <string.h>

void accum(const char* s, char* result) {
    int i, j;
    for (i = 0; s[i]; i++) {
        char c = s[i];
        if (isalpha(c)) {
            result[i * 2] = toupper(c);
            for (j = 0; j < i; j++) {
                result[i * 2 + j + 1] = tolower(c);
            }
            if (s[i + 1]) {
                result[i * 2 + j + 1] = '-';
            }
        }
    }
    result[i * 2] = '\0';
}

int main() {
    char result[100];
    accum("abcd", result);
    printf("%s\n", result);  // "A-Bb-Ccc-Dddd"
    accum("RqaEzty", result);
    printf("%s\n", result);  // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    accum("cwAt", result);
    printf("%s\n", result);  // "C-Ww-Aaa-Tttt"
    return 0;
}