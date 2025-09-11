#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* accum(const char *s) {
    int len = strlen(s);
    char *result = malloc(len * 4 + 1); // each character can be repeated len times, plus "-" and null terminator
    int resultIndex = 0;

    for (int i = 0; i < len; i++) {
        if (i > 0) {
            result[resultIndex++] = '-';
        }
        result[resultIndex++] = toupper(s[i]);
        for (int j = 0; j < i; j++) {
            result[resultIndex++] = tolower(s[i]);
        }
    }
    result[resultIndex] = '\0';
    return result;
}

int main() {
    char *s = accum("abcd");
    printf("%s\n", s);
    free(s);

    s = accum("RqaEzty");
    printf("%s\n", s);
    free(s);

    s = accum("cwAt");
    printf("%s\n", s);
    free(s);

    return 0;
}