#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longest(const char* s1, const char* s2) {
    int count[26] = {0};
    for (int i = 0; s1[i]; i++) {
        count[s1[i] - 'a'] = 1;
    }
    for (int i = 0; s2[i]; i++) {
        count[s2[i] - 'a'] = 1;
    }
    char* result = (char*)malloc(27);
    int idx = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i]) {
            result[idx++] = 'a' + i;
        }
    }
    result[idx] = '\0';
    return result;
}

int main() {
    printf("%s\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq"));  // "abcdefklmopqwxy"
    printf("%s\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"));  // "abcdefghijklmnopqrstuvwxyz"
    printf("%s\n", longest("abcd", "efgh"));  // "abcdefgh"
    printf("%s\n", longest("aaa", "bbb"));  // "ab"
    printf("%s\n", longest("hello", "world"));  // "dehlorw"
    return 0;
}