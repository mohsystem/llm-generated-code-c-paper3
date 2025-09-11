#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest(char* s1, char* s2) {
    int count[26] = {0};
    for (int i = 0; s1[i]; i++) {
        count[s1[i] - 'a'] = 1;
    }
    for (int i = 0; s2[i]; i++) {
        count[s2[i] - 'a'] = 1;
    }
    char* result = (char*)malloc(27);
    int index = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i]) {
            result[index++] = 'a' + i;
        }
    }
    result[index] = '\0';
    return result;
}

int main() {
    printf("%s\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq"));  // "abcdefklmopqwxy"
    printf("%s\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"));  // "abcdefghijklmnopqrstuvwxyz"
    return 0;
}