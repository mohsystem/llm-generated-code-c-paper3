#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int cmpfunc(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

char* longest(const char* s1, const char* s2) {
    bool charSet[26] = { false };
    for (int i = 0; s1[i] != '\0'; i++) {
        charSet[s1[i] - 'a'] = true;
    }
    for (int i = 0; s2[i] != '\0'; i++) {
        charSet[s2[i] - 'a'] = true;
    }
    char* result = (char*)malloc(27 * sizeof(char)); // 26 letters + 1 for '\0'
    int index = 0;
    for (int i = 0; i < 26; i++) {
        if (charSet[i]) {
            result[index++] = 'a' + i;
        }
    }
    result[index] = '\0';
    return result;
}

int main() {
    char* result;
    result = longest("xyaabbbccccdefww", "xxxxyyyyabklmopq");
    printf("%s\n", result);
    free(result);

    result = longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    printf("%s\n", result);
    free(result);

    result = longest("abc", "def");
    printf("%s\n", result);
    free(result);

    result = longest("abc", "cba");
    printf("%s\n", result);
    free(result);

    result = longest("abcd", "efgh");
    printf("%s\n", result);
    free(result);

    return 0;
}