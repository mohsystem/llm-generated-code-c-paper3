#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getDupSubstring(const char* s, int length) {
    int n = strlen(s);
    char* result = NULL;
    int setSize = n - length + 1;
    char** seen = (char**)malloc(setSize * sizeof(char*));

    for (int i = 0; i < setSize; i++) {
        seen[i] = NULL;
    }

    for (int i = 0; i <= n - length; i++) {
        char* substr = (char*)malloc((length + 1) * sizeof(char));
        strncpy(substr, &s[i], length);
        substr[length] = '\0';

        for (int j = 0; j < i; j++) {
            if (seen[j] && strcmp(seen[j], substr) == 0) {
                result = substr;
                goto cleanup;
            }
        }
        seen[i] = substr;
    }

cleanup:
    for (int i = 0; i < setSize; i++) {
        if (seen[i]) free(seen[i]);
    }
    free(seen);
    return result;
}

char* longestDupSubstring(const char* s) {
    int n = strlen(s);
    int left = 1, right = n;
    char* result = "";

    while (left < right) {
        int mid = left + (right - left) / 2;
        char* dup = getDupSubstring(s, mid);
        if (dup) {
            result = dup;
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return result;
}

int main() {
    printf("%s\n", longestDupSubstring("banana")); // "ana"
    printf("%s\n", longestDupSubstring("abcd"));   // ""
    printf("%s\n", longestDupSubstring("abababab")); // "abab"
    printf("%s\n", longestDupSubstring("abcdeabcde")); // "abcde"
    printf("%s\n", longestDupSubstring("aaaaa"));  // "aaaa"
    return 0;
}