#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void longest(const char* s1, const char* s2, char* result) {
    int count[26] = {0};
    for (int i = 0; s1[i]; i++) {
        count[s1[i] - 'a'] = 1;
    }
    for (int i = 0; s2[i]; i++) {
        count[s2[i] - 'a'] = 1;
    }
    int index = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i]) {
            result[index++] = 'a' + i;
        }
    }
    result[index] = '\0';
}

int main() {
    char result[27];
    longest("xyaabbbccccdefww", "xxxxyyyyabklmopq", result);
    printf("%s\n", result); // "abcdefklmopqwxy"
    longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", result);
    printf("%s\n", result); // "abcdefghijklmnopqrstuvwxyz"
    longest("abc", "def", result);
    printf("%s\n", result); // "abcdef"
    longest("abc", "abc", result);
    printf("%s\n", result); // "abc"
    longest("", "", result);
    printf("%s\n", result); // ""
    return 0;
}