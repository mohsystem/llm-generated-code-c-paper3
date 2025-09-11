#include <stdio.h>
#include <string.h>

char* longestDupSubstring(const char* s) {
    int n = strlen(s);
    char* longest = NULL;
    int longestLen = 0;
    for (int len = n / 2; len > 0; --len) {
        for (int i = 0; i <= n - len; ++i) {
            char substr[len + 1];
            strncpy(substr, s + i, len);
            substr[len] = '\0';
            char* found = strstr(s + i + 1, substr);
            if (found != NULL && len > longestLen) {
                if (longest != NULL) free(longest);
                longest = malloc(len + 1);
                strcpy(longest, substr);
                longestLen = len;
            }
        }
        if (longestLen > 0) break;
    }
    return longest;
}

int main() {
    const char* testCases[] = {"banana", "abcd", "abcabc", "aaaaaa"};
    for (int i = 0; i < 4; ++i) {
        printf("Input: %s\n", testCases[i]);
        char* result = longestDupSubstring(testCases[i]);
        printf("Output: %s\n\n", result ? result : "");
        if (result) free(result);
    }
    return 0;
}