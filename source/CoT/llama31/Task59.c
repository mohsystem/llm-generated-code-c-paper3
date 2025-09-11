// C code
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* accum(char* str) {
    int len = strlen(str);
    char* result = malloc((len * len + len) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < len; i++) {
        char c = str[i];
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                result[idx++] = toupper(c);
            } else {
                result[idx++] = tolower(c);
            }
        }
        if (i < len - 1) {
            result[idx++] = '-';
        }
    }
    result[idx] = '\0';
    return result;
}

int main() {
    char* test1 = accum("abcd");
    printf("%s\n", test1); free(test1); // "A-Bb-Ccc-Dddd"
    char* test2 = accum("RqaEzty");
    printf("%s\n", test2); free(test2); // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    char* test3 = accum("cwAt");
    printf("%s\n", test3); free(test3); // "C-Ww-Aaa-Tttt"
    char* test4 = accum("");
    printf("%s\n", test4); free(test4); // ""
    char* test5 = accum("a");
    printf("%s\n", test5); free(test5); // "A"
    return 0;
}