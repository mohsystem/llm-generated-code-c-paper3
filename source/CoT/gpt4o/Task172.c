#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countDistinctConcatenatedSubstrings(const char* text) {
    int n = strlen(text);
    int count = 0;
    char** seen = (char**)malloc(n * n * sizeof(char*));
    int seen_count = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int len = j - i;
            if (len % 2 == 0) {
                int half = len / 2;
                if (strncmp(text + i, text + i + half, half) == 0) {
                    char* sub = (char*)malloc((len + 1) * sizeof(char));
                    strncpy(sub, text + i, len);
                    sub[len] = '\0';

                    int already_seen = 0;
                    for (int k = 0; k < seen_count; ++k) {
                        if (strcmp(seen[k], sub) == 0) {
                            already_seen = 1;
                            break;
                        }
                    }
                    if (!already_seen) {
                        seen[seen_count++] = sub;
                        ++count;
                    } else {
                        free(sub);
                    }
                }
            }
        }
    }

    for (int k = 0; k < seen_count; ++k) {
        free(seen[k]);
    }
    free(seen);
    return count;
}

int main() {
    printf("%d\n", countDistinctConcatenatedSubstrings("abcabcabc")); // Output: 3
    printf("%d\n", countDistinctConcatenatedSubstrings("leetcodeleetcode")); // Output: 2
    printf("%d\n", countDistinctConcatenatedSubstrings("aabbccdd")); // Output: 0
    printf("%d\n", countDistinctConcatenatedSubstrings("ababab")); // Output: 2
    printf("%d\n", countDistinctConcatenatedSubstrings("aa")); // Output: 1
    return 0;
}