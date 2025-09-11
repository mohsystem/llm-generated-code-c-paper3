#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* accum(const char* s) {
    static char result[256]; // Ensure the buffer is large enough
    char *ptr = result;
    size_t length = strlen(s);
    
    for (size_t i = 0; i < length; ++i) {
        if (i > 0) {
            *ptr++ = '-';
        }
        *ptr++ = toupper(s[i]);
        for (size_t j = 0; j < i; ++j) {
            *ptr++ = tolower(s[i]);
        }
    }
    *ptr = '\0';
    return result;
}

int main() {
    printf("%s\n", accum("abcd"));  // A-Bb-Ccc-Dddd
    printf("%s\n", accum("RqaEzty"));  // R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy
    printf("%s\n", accum("cwAt"));  // C-Ww-Aaa-Tttt
    printf("%s\n", accum("abcD"));  // A-Bb-Ccc-Dddd
    printf("%s\n", accum("XYZ"));  // X-Yy-Zzz
    return 0;
}