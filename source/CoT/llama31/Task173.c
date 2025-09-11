#include <stdio.h>
#include <string.h>

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    char* longest = NULL;
    for (int len = n / 2; len > 0; len--) {
        for (int i = 0; i <= n - len; i++) {
            char substr[len + 1];
            strncpy(substr, s + i, len);
            substr[len] = '\0';
            char* found = strstr(s + i + 1, substr);
            if (found != NULL && (longest == NULL || strlen(substr) > strlen(longest))) {
                if (longest != NULL) free(longest);
                longest = malloc(strlen(substr) + 1);
                strcpy(longest, substr);
            }
        }
        if (longest != NULL) break;
    }
    return longest;
}

int main() {
    char s1[] = "banana";
    char s2[] = "abcd";
    char s3[] = "aabbcc";
    char s4[] = "abcabc";
    char s5[] = "abcdef";

    printf("%s\n", longestDupSubstring(s1)); // "ana"
    printf("%s\n", longestDupSubstring(s2)); // ""
    printf("%s\n", longestDupSubstring(s3)); // "bb"
    printf("%s\n", longestDupSubstring(s4)); // "abc"
    printf("%s\n", longestDupSubstring(s5)); // ""

    return 0;
}