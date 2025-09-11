#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countDistinctTwiceConcatenatedSubstrings(const char *text) {
    int n = strlen(text);
    int substrCount = 0;
    char **substrings = (char **)malloc(n * n * sizeof(char *));
    for (int i = 0; i < n * n; ++i) substrings[i] = NULL;

    for (int len = 1; len <= n / 2; ++len) {
        for (int i = 0; i + 2 * len <= n; ++i) {
            if (strncmp(text + i, text + i + len, len) == 0) {
                int found = 0;
                char *substring = strndup(text + i, 2 * len);
                for (int j = 0; j < substrCount; ++j) {
                    if (strcmp(substrings[j], substring) == 0) {
                        found = 1;
                        free(substring);
                        break;
                    }
                }
                if (!found) {
                    substrings[substrCount++] = substring;
                }
            }
        }
    }

    for (int i = 0; i < substrCount; ++i) {
        free(substrings[i]);
    }
    free(substrings);
    return substrCount;
}

int main() {
    printf("%d\n", countDistinctTwiceConcatenatedSubstrings("abcabcabc")); // 3
    printf("%d\n", countDistinctTwiceConcatenatedSubstrings("leetcodeleetcode")); // 2
    printf("%d\n", countDistinctTwiceConcatenatedSubstrings("aaa")); // 1
    printf("%d\n", countDistinctTwiceConcatenatedSubstrings("ababab")); // 2
    printf("%d\n", countDistinctTwiceConcatenatedSubstrings("xyzxyzxyz")); // 3
    return 0;
}