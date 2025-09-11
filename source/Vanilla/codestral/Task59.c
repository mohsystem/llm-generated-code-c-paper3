#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *accum(const char *s) {
    static char result[1000] = "";
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        if (i > 0) strcat(result, "-");
        strncat(result, &c, 1);
        for (int j = 0; j < i; j++) {
            strncat(result, &tolower(c), 1);
        }
    }
    return result;
}

int main() {
    printf("%s\n", accum("abcd")); // "A-Bb-Ccc-Dddd"
    printf("%s\n", accum("RqaEzty")); // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    printf("%s\n", accum("cwAt")); // "C-Ww-Aaa-Tttt"
    return 0;
}