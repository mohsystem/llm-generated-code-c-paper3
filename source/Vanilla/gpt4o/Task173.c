#include <stdio.h>
#include <string.h>

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    int start = 0, maxLen = 0;
    for (int len = 1; len < n; len++) {
        for (int i = 0; i <= n - len; i++) {
            for (int j = i + 1; j <= n - len; j++) {
                if (strncmp(s + i, s + j, len) == 0) {
                    if (len > maxLen) {
                        maxLen = len;
                        start = i;
                    }
                }
            }
        }
    }
    char* result = (char*)malloc(maxLen + 1);
    strncpy(result, s + start, maxLen);
    result[maxLen] = '\0';
    return result;
}

int main() {
    printf("%s\n", longestDupSubstring("banana")); // "ana"
    printf("%s\n", longestDupSubstring("abcd"));   // ""
    printf("%s\n", longestDupSubstring("abcabc")); // "abc"
    printf("%s\n", longestDupSubstring("aabcaabc")); // "aabc"
    printf("%s\n", longestDupSubstring("abcdabcde")); // "abcd"
    return 0;
}