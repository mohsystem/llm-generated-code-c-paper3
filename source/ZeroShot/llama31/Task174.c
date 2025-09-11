#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* shortestPalindrome(char* s) {
    int len = strlen(s);
    char* rev = (char*)malloc(len + 1);
    strcpy(rev, s);
    strrev(rev);
    for (int i = 0; i <= len; i++) {
        if (strncmp(s, rev + i, len - i) == 0) {
            char* result = (char*)malloc(len + i + 1);
            strncpy(result, rev, i);
            result[i] = '\0';
            strcat(result, s);
            free(rev);
            return result;
        }
    }
    free(rev);
    return NULL;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // "aaacecaaa"
    printf("%s\n", shortestPalindrome("abcd")); // "dcbabcd"
    printf("%s\n", shortestPalindrome("a")); // "a"
    printf("%s\n", shortestPalindrome("aa")); // "aa"
    printf("%s\n", shortestPalindrome("abcddcba")); // "abcddcba"
    return 0;
}