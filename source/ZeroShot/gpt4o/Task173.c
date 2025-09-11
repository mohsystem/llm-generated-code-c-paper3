#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    int left = 1, right = n;
    char* result = (char*)calloc(n + 1, sizeof(char));

    while (left <= right) {
        int mid = left + (right - left) / 2;
        char* dup = findDuplicate(s, n, mid);
        if (dup) {
            strcpy(result, dup);
            left = mid + 1;
            free(dup);
        } else {
            right = mid - 1;
        }
    }
    return result;
}

char* findDuplicate(char* s, int n, int len) {
    char** seen = (char**)calloc(n, sizeof(char*));
    for (int i = 0; i < n - len + 1; ++i) {
        char* substr = (char*)calloc(len + 1, sizeof(char));
        strncpy(substr, s + i, len);
        for (int j = 0; j < i; ++j) {
            if (seen[j] && strcmp(seen[j], substr) == 0) {
                for (int k = 0; k <= i; ++k) free(seen[k]);
                free(seen);
                return substr;
            }
        }
        seen[i] = substr;
    }
    for (int i = 0; i < n; ++i) free(seen[i]);
    free(seen);
    return NULL;
}

int main() {
    printf("%s\n", longestDupSubstring("banana")); // "ana"
    printf("%s\n", longestDupSubstring("abcd"));   // ""
    printf("%s\n", longestDupSubstring("ababc"));  // "ab"
    printf("%s\n", longestDupSubstring("aaaaa"));  // "aaaa"
    printf("%s\n", longestDupSubstring("abcabc")); // "abc"
    return 0;
}