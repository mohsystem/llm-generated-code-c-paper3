#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest(char *s1, char *s2) {
    int set[26] = {0};
    int len = 0;
    for (int i = 0; s1[i]; i++) {
        set[s1[i] - 'a'] = 1;
    }
    for (int i = 0; s2[i]; i++) {
        set[s2[i] - 'a'] = 1;
    }
    for (int i = 0; i < 26; i++) {
        if (set[i]) {
            len++;
        }
    }
    char *result = malloc(len + 1);
    int index = 0;
    for (int i = 0; i < 26; i++) {
        if (set[i]) {
            result[index++] = 'a' + i;
        }
    }
    result[index] = '\0';
    return result;
}

int main() {
    printf("%s\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq")); // "abcdefklmopqwxy"
    printf("%s\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz")); // "abcdefghijklmnopqrstuvwxyz"
    return 0;
}