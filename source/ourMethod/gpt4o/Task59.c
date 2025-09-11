#include <stdio.h>
#include <string.h>
#include <ctype.h>

void accum(const char* s, char* result) {
    int len = strlen(s);
    int pos = 0;
    for (int i = 0; i < len; ++i) {
        if (i != 0) {
            result[pos++] = '-';
        }
        result[pos++] = toupper(s[i]);
        for (int j = 0; j < i; ++j) {
            result[pos++] = tolower(s[i]);
        }
    }
    result[pos] = '\0';
}

int main() {
    char result[100];
    accum("abcd", result);
    printf("%s\n", result);  // Output: "A-Bb-Ccc-Dddd"
    accum("RqaEzty", result);
    printf("%s\n", result);  // Output: "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    accum("cwAt", result);
    printf("%s\n", result);  // Output: "C-Ww-Aaa-Tttt"
    accum("xYz", result);
    printf("%s\n", result);  // Output: "X-Yy-Zzz"
    accum("mM", result);
    printf("%s\n", result);  // Output: "M-Mm"
    return 0;
}